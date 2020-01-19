// 
// 
// 

#include "AlertInfoNode.h"

#include "objects.h"
#include "consts.h"
#include "function.h"
#include "Alerting.h"

void AlertInfoNodeClass::show()
{
	String data = Alerting.Print();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(50));
	if (_olddata == data)
	{
		return;
	}
	_olddata = data;	
	_data = data;
	Serial.print(gettextprj(50));
	Serial.print(gettextprj(212));
	Serial.println(_data);

	pos = 0;
	if (StrLength(_data) > LCDCOLS)
	{
		lcd.setCursor(0, 0);
		lcd.print(gettextprj(50));
		_data = gettextprj(112) + _data + gettextprj(112);
	}
	else
	{
		baseShowData(2, gettextprj(50), _data);

	}


}




void AlertInfoNodeClass::refresh()
{
	if (StrLength(_data) > LCDCOLS)
	{
		printLine(SCROLLSPEED);
	}
}


void AlertInfoNodeClass::printLine(int refreshMSeconds) {
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


