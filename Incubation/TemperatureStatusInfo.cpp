// 
// 
// 

#include "TemperatureStatusInfo.h"
#include "consts.h"
#include "function.h"
#include "objects.h"
#include "Alerting.h"

void TemperatureStatusInfoClass::printTemp(byte ind)
{

	float tempC = sensors.getTempC(lDev[ind]->addr);
	if (tempC > -127)
	{
		if (tempC > _max)
			_max = tempC;
		if (tempC < _min)
			_min = tempC;

		lcd.print(tempC, 1);
		Serial.print(tempC, 1);
		Serial3.print(tempC, 1);
	}
	else
	{
		Serial.print(gettextprj(249));
		Serial3.print(gettextprj(249));
		lcd.print(gettextprj(249));
	}

}

TemperatureStatusInfoClass::TemperatureStatusInfoClass()
{

	byte ind = sensors.getDeviceCount();

	lDev = new address*[ind];

	for (byte i = 0; i < ind; i++)
	{
		lDev[i] = new address();
		sensors.getAddress(lDev[i]->addr, i);
		sensors.setResolution(lDev[i]->addr, TEMPERATURE_PRECISION);
	}
}

TemperatureStatusInfoClass::~TemperatureStatusInfoClass()
{
	byte ind = sensors.getDeviceCount();

	for (byte i = 0; i < ind; i++)
	{
		delete lDev[i];
	}
	delete lDev;
}

void TemperatureStatusInfoClass::show()
{

	byte ind = sensors.getDeviceCount();
	sensors.requestTemperatures();

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(43));
	lcd.setCursor(0, 1);
	lcd.print(gettextprj(44));

	lcd.setCursor(3, 0);

	_max = 0;
	_min = 100;

	Serial.print(gettextprj(207));
	Serial3.print(gettextprj(207));

	Serial.print(gettextprj(208));
	Serial3.print(gettextprj(208));
	if (ind >= 1)
	{
		printTemp(0);
	}
	else
	{
		Serial.print(gettextprj(249));
		Serial3.print(gettextprj(249));
		lcd.print(gettextprj(249));
	}

	Serial.print(gettextprj(209));
	Serial3.print(gettextprj(209));

	lcd.setCursor(11, 0);
	if (ind >= 2)
	{
		printTemp(1);
	}
	else
	{
		lcd.print(gettextprj(249));
		Serial.print(gettextprj(249));
		Serial3.print(gettextprj(249));

	}

	Serial.print(gettextprj(210));
	Serial3.print(gettextprj(210));

	lcd.setCursor(3, 1);
	if (ind >= 3)
	{
		printTemp(2);
	}
	else
	{
		lcd.print(gettextprj(249));
		Serial.print(gettextprj(249));
		Serial3.print(gettextprj(249));
	}

	Serial.print(gettextprj(211));
	Serial3.print(gettextprj(211));

	lcd.setCursor(11, 1);
	if (ind >= 4)
	{
		printTemp(3);
	}
	else
	{
		lcd.print(gettextprj(249));
		Serial.print(gettextprj(249));
		Serial3.print(gettextprj(249));
	}

	Serial.println("");
	Serial3.println("");
	if (currentTemp > _max)
		_max = currentTemp;
	if (currentTemp < _min)
		_min = currentTemp;


	float temp = currentSetTemp;

	if (abs(_max - temp) > alTmpMax || abs(temp - _min) > alTmpMax)
	{
		Alerting.Start(at_temp);
	}
	else
		Alerting.Finish(at_temp);

}
