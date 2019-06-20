// 
// 
// 

#include "StatusMainInfo.h"
#include "function.h"
#include "objects.h"
#include "consts.h"
#include "Alerting.h"


bool StatusMainInfoClass::allowInner()
{
	return _work;
}

bool StatusMainInfoClass::allowNext()
{
	return _work;
}

bool StatusMainInfoClass::allowPrev()
{
	return _work;
}

void StatusMainInfoClass::show()
{
	lcd.clear();
	_timer = millis();
	float humd = myHumidity.readHumidity();

	if (started == 0)
	{
		_work = false;
		Alerting.Start(at_endplan);
		lcd.setCursor(0, 0);
		lcd.print(gettextprj(45));
		lcd.setCursor(0, 1);
		lcd.print(gettextprj(46));

		Serial.print(gettextprj(45));
		Serial.print("  ");
		Serial.println(gettextprj(46));


	}
	else if (humd >= 997)
	{
		_work = false;
		Alerting.Start(at_hum);
		lcd.setCursor(0, 0);
		lcd.print(gettextprj(41));
		lcd.setCursor(0, 1);
		lcd.print(gettextprj(42));

		Serial.print(gettextprj(41));
		Serial.print("  ");
		Serial.println(gettextprj(42));


	}
	else
	{
		_work = true;
		//Alerting.Finish(at_hum);
		lcd.setCursor(0, 0);
		lcd.print(gettextprj(39));
		lcd.setCursor(0, 1);
		lcd.print(gettextprj(40));

		lcd.setCursor(5, 0);
		lcd.print(currentSetTemp, 1);
		lcd.setCursor(5, 1);
		lcd.print(currentRow.GetHum() + BASEHUM);

		currentTemp = myHumidity.readTemperature();
		lcd.setCursor(12, 0);
		lcd.print(myHumidity.readTemperature(), 1);
		lcd.setCursor(12, 1);
		lcd.print(humd, 0);

		Serial.print(gettextprj(204));
		Serial.print(currentRow.GetTemp() / 10.0 + BASETEMP, 1);
		Serial.print(gettextprj(205));
		Serial.println(currentTemp, 1);

		Serial.print(gettextprj(206));
		Serial.print(currentRow.GetHum() + BASEHUM, 1);
		Serial.print(gettextprj(205));
		Serial.println(humd, 1);

		Serial3.print(gettextprj(204));
		Serial3.print(currentRow.GetTemp() / 10.0 + BASETEMP, 1);
		Serial3.print(gettextprj(205));
		Serial3.println(currentTemp, 1);

		Serial3.print(gettextprj(206));
		Serial3.print(currentRow.GetHum() + BASEHUM, 1);
		Serial3.print(gettextprj(205));
		Serial3.println(humd, 1);
	}
	currentHumd = humd;

}

void StatusMainInfoClass::refresh()
{
	if (!_work)
	{
		if (started == 1)
		{
			_work = true;
			
		}
		return;
	}
		
	if (abs(millis() - _timer) < ERRORINTERVAL)
	{
		return;
	}
	_timer = millis();
	if (started == 0)
	{

	}
	else if (myHumidity.readHumidity() > 997)
	{

	}
	else
	{
		if (abs(currentHumd - (currentRow.GetHum() + BASEHUM)) > alHumMax)
		{
			Alerting.Start(at_hum);
		}
		else
			Alerting.Finish(at_hum);

	}

}
