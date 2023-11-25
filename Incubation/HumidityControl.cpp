// 
// 
// 

#include "HumidityControl.h"
#include "consts.h"
#include "objects.h"
#include "Alerting.h"
#include "VentilationControl.h"
#include "StatusInfo.h"


HumidityControlClass HumidityControl;


void HumidityControlClass::funcontrol()
{
	float temp = currentRow.GetHum() + BASEHUM;
	float base = currentHumd - temp;


	if (base <= 0)
	{
		VentilationControl.SetSpeed(0, fu_hum);
		StatusInfo.AddStatus(so_dry, 0);
		return;
	}



	if (base >= alHumMax)
	{
		StatusInfo.AddStatus(so_dry, 0xFF);
		VentilationControl.SetSpeed(0xFF, fu_hum);
		return;
	}


	
	if (base > alHumDel)
	{
	
		double data = 0xFF / (double)sq(alHumMax);
		double cntrl = sq(base) * data;

		if (minhum * 2.6 > cntrl)
			cntrl = minhum * 2.6;

		StatusInfo.AddStatus(so_dry, cntrl);
		VentilationControl.SetSpeed(cntrl, fu_hum);
	}
}

void HumidityControlClass::wait()
{

	StatusInfo.AddStatus(so_dry, 0);
	StatusInfo.AddStatus(so_wet, 0);
	VentilationControl.SetSpeed(0, fu_hum);
	digitalWrite(FANPIN, LOW);

}



void HumidityControlClass::refresh()
{

	if (currentHumd >= 997)
	{
		digitalWrite(FANPIN, LOW);
		StatusInfo.AddStatus(so_wet, 0);
		return;
	}

	funcontrol();

	float temp = currentRow.GetHum() + BASEHUM;

	float base = temp - currentHumd;

	if (base <= 0)
	{
		
		digitalWrite(FANPIN, LOW);
		StatusInfo.AddStatus(so_wet, 0);
		return;
	}

	if (base >= alHumMax)
	{
		digitalWrite(FANPIN, HIGH);
		StatusInfo.AddStatus(so_wet, 0xFF);
		return;
	}

	

	if (base > alHumDel )
	{
		
		double data = 0xFF / (double)sq(alHumMax);
		double cntrl = sq(base) * data;

		if (minhum * 2.6 > cntrl)
			cntrl = minhum * 2.6;

		_delta = (255.0 - cntrl) * PEEKVALUE / PEEKDEV;

		if (cntrl > 0)
		{
			if (cntrl >= 255 || _delta < PEEKVALUE)
			{
				StatusInfo.AddStatus(so_wet, 0xFF);
				digitalWrite(FANPIN, LOW);
				return;
			}

			StatusInfo.AddStatus(so_wet, cntrl);
			if (_on)
			{
				if (abs(millis() - _timer) > PEEKVALUE)
				{
					_timer = millis();
					_on = false;

					digitalWrite(FANPIN, LOW);
				}
			}
			else
			{
				if (abs(millis() - _timer) > _delta)
				{
					_timer = millis();
					_on = true;

					digitalWrite(FANPIN, HIGH);
				}
			}


		}
		else
		{
			StatusInfo.AddStatus(so_wet, 0);
			digitalWrite(FANPIN, HIGH);
		}
	}
}

