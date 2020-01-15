/*
 Name:		Incubation.ino
 Created:	3/30/2017 4:29:43 PM
 Author:	Aleksey
*/


#include <Bounce2.h>
#include "AlertInfoNode.h"
#include "StatusInfo.h"
#include "ControlSession.h"
#include "HumidityControl.h"
#include "VentilationControl.h"
#include "HeatingControl.h"
#include <TimeLib.h>
#include <Time.h>
#include <EEPROM.h>
#include <DS1307RTC.h>
#include "NodeManager.h"
#include "objects.h"
#include "Alerting.h"

unsigned long timer = 0;

void setup() {
	Serial.begin(9600);
	Serial.println(F("Start incubation project full log"));


	pinMode(BUTTON_U, INPUT_PULLUP);
	pinMode(BUTTON_R, INPUT_PULLUP);
	pinMode(BUTTON_L, INPUT_PULLUP);
	lcd.begin(LCDCOLS, LCDROWS);  // initializes the 16x2 LCD
	pinMode(ALARMLEDPIN, OUTPUT);
	pinMode(ALARMSOUNDPIN, OUTPUT);
	digitalWrite(ALARMLEDPIN, LOW);
	digitalWrite(ALARMSOUNDPIN, LOW);

	pinMode(DOOREPIN, INPUT_PULLUP);
	pinMode(TRAYLEFTPIN, OUTPUT);
	digitalWrite(TRAYLEFTPIN, LOW);
	pinMode(TRAYRIGHTPIN, OUTPUT);
	digitalWrite(TRAYRIGHTPIN, LOW);
	pinMode(TRAYCENTERPIN, INPUT_PULLUP);

	pinMode(HEATCONTROL, OUTPUT);
	digitalWrite(HEATCONTROL, 0);
	pinMode(FANPIN, OUTPUT);
	digitalWrite(FANPIN, HIGH);
	pinMode(COOLERPIN, OUTPUT);
	digitalWrite(COOLERPIN, HIGH);


	myHumidity.begin();
	setSyncProvider(RTC.get);
	sensors.begin();


	for (int i = 0; i < 3; i++)
	{
		bState[i] = btn_up;
	}

	if (digitalRead(BUTTON_D) == LOW)
	{
		pinMode(RESETLEDPIN, OUTPUT);
		unsigned long timer = millis();
		while (digitalRead(BUTTON_D) == LOW)
		{
			digitalWrite(RESETLEDPIN, HIGH); // turn the LED on (HIGH is the voltage level)
			delay(50); // wait for a second
			if (abs(millis() - timer) < RESETINTERVAL)
				digitalWrite(RESETLEDPIN, LOW); // turn the LED off by making the voltage LOW
			delay(50);
		}
		if (abs(millis() - timer) > RESETINTERVAL)
		{
			for (int i = 0; i < EEPROM.length(); i++) {
				EEPROM.write(i, 0);
			}

			currentRow.writeRow(0, 0, 11, 37.9, 66, 4, 20, 30);
			currentRow.save();

			currentRow.writeRow(0, 1, 6, 37.3, 53, 4, 2, 5);
			currentRow.save();

			currentRow.writeRow(0, 2, 2, 37.3, 47, 4, 2, 20);
			currentRow.save();

			currentRow.writeRow(0, 3, 2, 37.9, 66, 0, 2, 5);
			currentRow.save();


			currentRow.writeRow(1, 0, 8, 38, 70, 4, 0, 0);
			currentRow.save();

			currentRow.writeRow(1, 1, 4, 37.5, 60, 4, 1, 5);
			currentRow.save();

			currentRow.writeRow(1, 2, 10, 37.2, 56, 4, 2, 20);
			currentRow.save();

			currentRow.writeRow(1, 3, 3, 37, 70, 0, 1, 10);
			currentRow.save();



			currentRow.writeRow(2, 0, 16, 38, 60, 4, 1, 5);
			currentRow.save();

			currentRow.writeRow(2, 1, 10, 37.5, 52, 4, 2, 20);
			currentRow.save();

			currentRow.writeRow(2, 2, 2, 37.2, 70, 0, 1, 10);
			currentRow.save();

			currentRow.writeRow(2, 3, 2, 37, 70, 0, 0, 0);
			currentRow.save();



			currentRow.writeRow(3, 0, 3, 37.8, 55, 4, 0, 0);
			currentRow.save();

			currentRow.writeRow(3, 1, 8, 37.5, 52, 4, 1, 5);
			currentRow.save();

			currentRow.writeRow(3, 2, 10, 37.2, 52, 4, 3, 20);
			currentRow.save();

			currentRow.writeRow(3, 3, 2, 37.0, 70, 0, 1, 10);
			currentRow.save();


			currentRow.writeRow(4, 0, 6, 37.8, 55, 4, 0, 0);
			currentRow.save();

			currentRow.writeRow(4, 1, 8, 37.5, 52, 4, 1, 5);
			currentRow.save();

			currentRow.writeRow(4, 2, 13, 37.2, 52, 4, 2, 20);
			currentRow.save();

			currentRow.writeRow(4, 3, 2, 37, 70, 0, 1, 10);
			currentRow.save();


			currentRow.writeRow(5, 0, 12, 37.6, 58, 4, 1, 5);
			currentRow.save();

			currentRow.writeRow(5, 1, 4, 37.3, 53, 4, 1, 20);
			currentRow.save();

			currentRow.writeRow(5, 2, 2, 37.2, 47, 0, 0, 0);
			currentRow.save();

			currentRow.writeRow(5, 3, 2, 37, 66, 0, 0, 0);
			currentRow.save();

			for (byte i = 0; i < 3; i++)
			{
				digitalWrite(RESETLEDPIN, HIGH); // turn the LED on (HIGH is the voltage level)
				delay(500); // wait for a second
				digitalWrite(RESETLEDPIN, LOW); // turn the LED off by making the voltage LOW
				delay(500);
			}
		}

	}

	currentDay = 1;
	currentPeriod = 0;
	currentTable = 0;
	started = 0;
	timerUpdated = 1;

	bright = 50;
	contr = 90;
	alTmpDel = 1;
	alTmpMax = 2;
	alHumDel = 5;
	alHumMax = 15;
	toroot = false;
	minheat = 15;
	minhum = 15;

	int val = EEPROM.read(2);
	if (val != 0)
	{
		bright = EEPROM.read(0);
		contr = EEPROM.read(1);
		alTmpDel = EEPROM.read(3);
		alTmpMax = EEPROM.read(4);
		alHumDel = EEPROM.read(5);
		alHumMax = EEPROM.read(6);
		currentDay = EEPROM.read(13);
		currentPeriod = EEPROM.read(14);
		currentTable = EEPROM.read(15);
		started = EEPROM.read(16);
		currentHour = EEPROM.read(17);

		minheat = EEPROM.read(18);
		minhum = EEPROM.read(19);

	}
	else
	{
		EEPROM.update(0, bright);
		EEPROM.update(1, contr);
		EEPROM.update(3, alTmpDel);
		EEPROM.update(4, alTmpMax);
		EEPROM.update(5, alHumDel);
		EEPROM.update(6, alHumMax);

		EEPROM.update(13, currentDay);
		EEPROM.update(14, currentPeriod);
		EEPROM.update(15, currentTable);

		EEPROM.update(16, started);
		EEPROM.update(17, currentHour);

		EEPROM.update(18, minheat);
		EEPROM.update(19, minhum);

		EEPROM.update(2, timerUpdated);

	}

	adjustments.setup(BRITHPIN, CONTRPIN, bright, 100 - contr);

	

	NodeManager.init();
	currentRow.init(currentPeriod, currentTable);

	ControlSession.init();

	lcd.clear();
	
}

int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

bool check = false;
byte sec = 0;


void loop() {
	
	
	if (abs(millis() - timer) > REFRESHDATA)
	{
		currentTemp = myHumidity.readTemperature();
		currentHumd = myHumidity.readHumidity();
		timer = millis();
	}

	if (hour() != currentHour)
	{
		currentHour = hour();
		EEPROM.update(17, currentHour);
		if (timerUpdated == 0)
		{
			if (RTC.chipPresent()) {
				timerUpdated = 1;
				RTC.set(now());   // set the RTC and the system time to the received value			
				EEPROM.update(17, timerUpdated);
			}

		}
	}
	if (currentDay != day())
	{
		currentDay = day();
		EEPROM.update(13, currentDay);
		ControlSession.init();
	}

	if (currentRow.GetDay() < day() - 1)
	{
		if (currentPeriod < 3)
		{
			currentPeriod++;
			currentDay = 0;
			currentHour = 0;
			currentRow.init(currentPeriod, currentTable);
			ControlSession.init();
			EEPROM.update(13, currentDay);
			EEPROM.update(14, currentPeriod);
			EEPROM.update(15, currentTable);
			EEPROM.update(16, 1);
			setTime(0, 0, 0, currentDay + 1, 1, 2017);		

			if (RTC.chipPresent()) {
				timerUpdated = 1;
				RTC.set(now());   
			}
			else
				timerUpdated = 0;
				
			EEPROM.update(17, timerUpdated );
		}
		else
		{
			Alerting.Start(at_endplan);
		}
	}
	
	ControlSession.refresh();

	if (ControlSession.Hum || ControlSession.Heet)
		VentilationControl.refresh();
	else
		VentilationControl.wait();

	if (ControlSession.Heet)
		HeatingControl.refresh();
	else
		HeatingControl.wait();

	if (ControlSession.Hum)
		HumidityControl.refresh();
	else
		HumidityControl.wait();




	Alerting.refresh();
	
	NodeManager.work();
	


		//if (second() % 10 == 0 && second() != sec)
		//{
		//	check = !check;
		//	sec = second();
		//}
		//if (check)
		//{
		//
		//	lcd.setCursor(0, 1);
		//	lcd.print(freeRam());
		//}
}





