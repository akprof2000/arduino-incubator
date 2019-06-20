// 
// 
// 
#include "ControlSession.h"
#include "objects.h"
#include "Time.h"
#include "TimeLib.h"
#include "Alerting.h"
#include "StatusInfo.h"
#include "VentilationControl.h"


timeshift ControlSessionClass::calculate(byte count)
{
	timeshift ts;

	for (size_t i = 0; i < 24; i++)
	{
		ts.min[i] = -1;
	}

	float sh = 24.0 / count;
	float ind = sh;

	for (;;)
	{
		if (ind > 25)
			break;

		if (ind >= 24)
		{
			ts.min[0] = 60.0 * (ind - (int)ind);

		}
		else
		{
			ts.min[(int)ind] = 60.0 * (ind - (int)ind);
		}
		ind = ind + sh;
	}

	return ts;
}

bool ControlSessionClass::compare(timeshift data)
{
	if (data.skip == true)
		return false;


	if (data.min[hour()] == minute())
	{
		return true;
	}

	return false;
}

void ControlSessionClass::init()
{
	if (currentRow.GetRotate() > 0)
	{
		_rotation = calculate(currentRow.GetRotate());
	}
	else
		_rotation.skip = true;

	if (currentRow.GetVentCount() > 0)
		_delayvent = calculate(currentRow.GetVentCount());
	else
		_delayvent.skip = true;

	if (currentRow.GetCoolCount() > 0)
		_delayfreze = calculate(currentRow.GetCoolCount());
	else
		_delayfreze.skip = true;

	if (_delayfreze.skip == false && _delayvent.skip == false)
	{
		_delayvent = calculate(currentRow.GetCoolCount() + currentRow.GetVentCount());
		_delayfreze = calculate(currentRow.GetCoolCount() + currentRow.GetVentCount());

		float dx = currentRow.GetVentCount() / (currentRow.GetCoolCount() + currentRow.GetVentCount());
		float dy = 1 - dx;
		float s = 0;

		for (size_t i = 0; i < 24; i++)
		{
			if (_delayvent.min[i] > -1)
			{
				if (s >= 0)
				{
					_delayfreze.min[i] = -1;					
					s = s - dx;
				}
				else
				{
					_delayvent.min[i] = -1;
					s = s + dy;
				}
			}

		}

	}


	_timing = millis();
	_rotchange = false;

	_starting = true;
}


ControlSessionClass ControlSession;

void ControlSessionClass::refresh()
{

	if (millis() + _refreshtimmer > REFRESHDATA)
	{
		_refreshtimmer = millis();
		_wait = 0;
		currentSetTemp = currentRow.GetTemp() / 10.0 + BASETEMP;
	}


	if (door.update() || _starting)
	{
		_starting = false;
		Alerting.SetWaitAllert();
		if (door.read() == HIGH)
		{
			
			_timing = millis();
			Hum = false;
			Heet = false;
			VentilationControl.wait();
			StatusInfo.AddStatus(so_door, 155);
			StatusInfo.AddStatus(so_cent, 155);

			_rotchange = !_rotchange;

			if (_rotchange)
			{
				digitalWrite(TRAYLEFTPIN, LOW);
				digitalWrite(TRAYRIGHTPIN, HIGH);
			}
			else
			{
				digitalWrite(TRAYLEFTPIN, HIGH);
				digitalWrite(TRAYRIGHTPIN, LOW);
			}

		}
		else
		{
			
			Hum = true;
			Heet = true;
			StatusInfo.AddStatus(so_door, 0);
			StatusInfo.AddStatus(so_cent, 0);
			Alerting.Finish(at_connect);
			_needrot = true;

		}
	}



	if (center.update())
	{
		if (center.read() == LOW)
		{
			if (door.read() == HIGH)
			{
				StatusInfo.AddStatus(so_cent, 0);
				digitalWrite(TRAYLEFTPIN, LOW);
				digitalWrite(TRAYRIGHTPIN, LOW);
			}
		}
	}




	if (door.read() == HIGH)
	{
		if (abs(millis() - _timing) > WAITOPENDOOR)
		{
			
			_timing = millis();
			Alerting.Start(at_connect);
		}
		return;
	}


	if (_rotate)
	{
		if (abs(millis() - _timerot) > ROTATEVENT)
		{
			_timerot = 0;
			_rotate = false;
			StatusInfo.AddStatus(so_rot, 0);
			//if (!NEEDCHANGEPIN)
			{
				digitalWrite(TRAYLEFTPIN, LOW);
				digitalWrite(TRAYRIGHTPIN, LOW);
			}
		}


	}
	else if (compare(_rotation) || _needrot)
	{
		StatusInfo.AddStatus(so_rot, 155);
		_needrot = false;
		_timerot = millis();
		_rotchange = !_rotchange;

		if (_rotchange)
		{
			digitalWrite(TRAYLEFTPIN, LOW);
			digitalWrite(TRAYRIGHTPIN, HIGH);
		}
		else
		{
			digitalWrite(TRAYLEFTPIN, HIGH);
			digitalWrite(TRAYRIGHTPIN, LOW);
		}

		_rotate = true;

	}

	if (_ventelate)
	{
		if (abs(millis() - _timevent) > (long)currentRow.GetVentTime() * 60 * 1000)
		{
			_timevent = 0;
			_ventelate = false;
			Hum = true;
			_wait = WAITAFTEREVENT;
			_timmer = millis();
			StatusInfo.AddStatus(so_blow, 0);
			VentilationControl.SetSpeed(0, fu_vent);
		}

	}
	else if (compare(_delayvent))
	{
		StatusInfo.AddStatus(so_blow, VENTDEFROTATE);
		VentilationControl.SetSpeed(VENTDEFROTATE, fu_vent);
		_timevent = millis();
		_ventelate = true;
		Hum = false;
	}

	
	if (_freeze)
	{
		currentSetTemp = currentRow.GetCoolHeat();

		if (abs(millis() - _timefreze) > (long)currentRow.GetCoolTime() * 60 * 1000)
		{
			_timefreze = 0;
			Hum = true;
			_wait = WAITAFTEREVENT;
			_timmer = millis();
			_freeze = false;
			StatusInfo.AddStatus(so_blow, 0);
			VentilationControl.SetSpeed(0, fu_vent);
			Alerting.SetWaitAllert();
		}
		else
		{
			VentilationControl.SetSpeed(VENTDEFROTATE, fu_vent);
		}
	}
	else if (compare(_delayfreze))
	{
		Alerting.SetWaitAllert();
		StatusInfo.AddStatus(so_blow, VENTDEFROTATE);		
		VentilationControl.SetSpeed(VENTDEFROTATE, fu_vent);
		_timefreze = millis();
		_freeze = true;
		Hum = false;
		
	}

}


