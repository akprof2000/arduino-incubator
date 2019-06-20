// 
// 
// 

#include <Time.h>
#include <TimeLib.h>

#include "CurrentTimeStatusNode.h"
#include "objects.h"


void CurrentTimeStatusNodeClass::init()
{


}

void CurrentTimeStatusNodeClass::show()
{	
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Т:       В:  ");
	


	lcd.setCursor(0, 1);
	
	lcd.print("Время: ");

	lcd.setCursor(3, 0);
	showCurrentH();
	lcd.setCursor(11, 0);
	showCurrentY();

}

void CurrentTimeStatusNodeClass::refresh()
{
	lcd.setCursor(7, 1);
	showCurrentTime();
}


void CurrentTimeStatusNodeClass::showCurrentTime() {

	//int sec = millis() / 1000;
	delay(500);
	lcd.print(hour());
	lcd.print(":");
	lcd.print(minute());
	lcd.print(":");
	lcd.print(second());

}


void  CurrentTimeStatusNodeClass::showCurrentH() {
	strProgress(25);
}

void  CurrentTimeStatusNodeClass::showCurrentY() {
	strProgress(78);
}

void  CurrentTimeStatusNodeClass::strProgress(byte val)
{
	
	if (val == 0)
		lcd.print("   ");
	else if (val < 15)
		lcd.print("\x01  ");
	else if (val < 30)
		lcd.print("\x02  ");
	else if (val < 45)
		lcd.print("\x03  ");
	else if (val < 60)
		lcd.print("\x03\x04 ");
	else if (val < 75)
		lcd.print("\x03\x05 ");
	else if (val < 90)
		lcd.print("\x03\x06 ");
	else
		lcd.print("\x03\x06\x07");
}






