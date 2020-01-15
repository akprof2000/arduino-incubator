// 
// 
// 

#include "CurrentOperation.h"
#include "objects.h"
#include "consts.h"
#include "function.h"
#include "StatusInfo.h"

void CurrentOperationClass::show()
{

	lcd.clear();
	_data = StatusInfo.Print();
	Serial.print(gettextprj(49));
	Serial.print(gettextprj(212));
	Serial.println(_data);

	pos = 0;
	if (StrLength(_data) > LCDCOLS)
	{
		baseShowData(2, gettextprj(49), "");
		_data = gettextprj(110) + _data + gettextprj(110);
	}
	else
	{
		baseShowData(2, gettextprj(49), _data);
	}

}




void CurrentOperationClass::refresh()
{
	if (StrLength(_data) > LCDCOLS)
	{
		printLine(SCROLLSPEED);	
	}
}


void CurrentOperationClass::printLine(int refreshMSeconds) {
	if (abs(millis() - _time) > refreshMSeconds) {
		int len = (int)_data.length();

		const char *message = _data.c_str();
		
		_time = millis();
		lcd.setCursor(0, 1);

		char lcdTop[LCDCOLS << 1];
		int copySize = LCDCOLS << 1;



		memcpy(&lcdTop[0], &message[pos], copySize);
		lcd.print(lcdTop);
		
		if (message[pos] < ' ')
			pos += 1;

		
		pos += 1;
		
		if (pos + LCDCOLS >= strlen(message))
		{
			pos = 0;
		}
			
	}

}

