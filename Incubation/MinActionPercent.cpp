// 
// 
// 


#include <EEPROM.h>

#include "MinActionPercent.h"
#include "objects.h"
#include "function.h"

bool MinActionPercentClass::allowInner()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}



bool MinActionPercentClass::allowNext()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}

bool MinActionPercentClass::allowPrev()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;

}

void MinActionPercentClass::showHeat()
{
	lcd.setCursor(12, 0);
	if (_blinc && _shift == 1)
	{
		lcd.print(gettextprj(252));
	}
	else
		lcd.print(minheat);



}

void MinActionPercentClass::showHum()
{
	lcd.setCursor(9, 1);
	if (_blinc && _shift == 2)
	{
		lcd.print(gettextprj(252));
	}
	else
		lcd.print(minhum);


}

void MinActionPercentClass::show()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(51));
	lcd.setCursor(0, 1);
	lcd.print(gettextprj(52));
	showHeat();
	showHum();
}

void MinActionPercentClass::refresh()
{
	if (bState[0] == btn_down && !appl[0])
	{
		_shift++;
		if (_shift >= 3)
		{
			_shift = 0;
		}
		EEPROM.update(18, minheat);
		EEPROM.update(19, minhum);
		appl[0] = true;
		_blinc = false;
		showHeat();
		showHum();

	}
	else
	{
		if (_shift == 1)
		{
			float val = minheat;
			if (scrollBar(0, 100, 1, val))
			{
				minheat = val;

			}
		}
		else if (_shift == 2)
		{
			float val = minhum;
			if (scrollBar(0, 100, 1, val))
			{
				minhum = val;

			}
		}

	}

	if (_shift > 0 && _shift < 3)
	{
		if (abs(millis() - _timer) > BLINKINTERVAL)
		{
			_timer = millis();
			_blinc = !_blinc;
		}

		showHeat();
		showHum();
	}


}


