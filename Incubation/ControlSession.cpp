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
	ts.count = 1440 / count;
	ts.startIt = ts.count / 2;
	ts.execute = true;
	ts.skip = false;
	return ts;
}

bool ControlSessionClass::compare(timeshift data)
{
	if (data.skip == true)
	{
		return false;
	}

	int mn = hour() * 60 + minute();
	mn = mn + data.startIt;

	

	if ((mn % data.count == 0) && (mn <= 1440))
	{
		if (data.execute == false)
		{
			data.execute = true;
			return true;
		}
	}
	else
	{
			data.execute = false;
	}

	return false;
}

void ControlSessionClass::init()
{
	center.update();
	if (center.read() == LOW)
	{
		StatusInfo.AddStatus(so_cent, 0);
		digitalWrite(TRAYLEFTPIN, LOW);
		digitalWrite(TRAYRIGHTPIN, LOW);
		_cetration = true;
		_needcenter = false;
	}

	if (currentRow.GetRotate() > 0)
	{
		_rotation = calculate(currentRow.GetRotate());
	}
	else
	{
		_rotation.skip = true;
		if (_cetration == false)
			_needcenter = true;
	}

	if (currentRow.GetVentCount() > 0)
		_delayvent = calculate(currentRow.GetVentCount());
	else
	{
		_delayvent.skip = true;

	}

	_timing = millis();
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
			
			if (_cetration == false)
			{
				_needcenter = true;
			}
		}
		else
		{
			Hum = true;
			Heet = true;
			StatusInfo.AddStatus(so_door, 0);
			Alerting.Finish(at_connect);
		}
	}


	if (center.update())
		if (center.read() == LOW)
		{
			if (_needcenter == true)
			{
				digitalWrite(TRAYLEFTPIN, LOW);
				digitalWrite(TRAYRIGHTPIN, LOW);
				_cetration = true;
				_needcenter = false;
			}
			StatusInfo.AddStatus(so_cent, 0);
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
	else if ((compare(_rotation) && door.read() == LOW) || _needcenter)
	{
		StatusInfo.AddStatus(so_rot, 155);
		_timerot = millis();
		_rotchange = !_rotchange;
		_cetration = false;
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

	if (door.read() == HIGH)
	{
		if (abs(millis() - _timing) > WAITOPENDOOR)
		{
			_timing = millis();
			Alerting.Start(at_connect);
		}

		if (Hum == true && Heet == true)
		{
			_starting = true;
		}

		return;
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


}


