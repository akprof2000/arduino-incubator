// 
// 
// 

#include "Time.h"
#include "TimeLib.h"
#include "TaskStatusInfo.h"
#include "function.h"
#include "objects.h"

void TaskStatusInfoClass::show()
{

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(47));
	lcd.setCursor(8, 0);
	lcd.print(gettextprj(12 + currentTable));
	lcd.setCursor(0, 1);
	lcd.print(gettextprj(48));
	lcd.setCursor(3, 1);
	lcd.print(currentPeriod + 1);
	lcd.setCursor(8, 1);
	if (day() < 10)
		lcd.print('0');
	lcd.print(day());
	lcd.setCursor(14, 1);
	if (hour() < 10)
		lcd.print('0');
	lcd.print(hour());

	Serial.print(gettextprj(200));
	Serial.print(gettextprj(12 + currentTable));
	Serial.print(gettextprj(201));
	Serial.print(currentPeriod + 1);
	Serial.print(gettextprj(202));
	Serial.print(day());
	Serial.print(gettextprj(213));
	Serial.print(hour());
	Serial.print(":");
	Serial.print(minute());
	Serial.print(":");
	Serial.println(second());

	Serial3.print(gettextprj(200));
	Serial3.print(gettextprj(12 + currentTable));
	Serial3.print(gettextprj(201));
	Serial3.print(currentPeriod + 1);
	Serial3.print(gettextprj(202));
	Serial3.print(day());
	Serial3.print(gettextprj(203));
	Serial3.println(hour());

}

