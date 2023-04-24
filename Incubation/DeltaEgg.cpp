//
//
//


#include <EEPROM.h>

#include "DeltaEgg.h"
#include "objects.h"
#include "function.h"

bool DeltaEggClass::allowInner()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}



bool DeltaEggClass::allowNext()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}

bool DeltaEggClass::allowPrev()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;

}

void DeltaEggClass::showMin()
{
	lcd.setCursor(12, 0);
	if (_blinc && _shift == 1)
	{
		lcd.print(gettextprj(250));
	}
	else
		lcd.print(deltaEggMin / 10.0);



}

void DeltaEggClass::showMax()
{
	lcd.setCursor(12, 1);
	if (_blinc && _shift == 2)
	{
		lcd.print(gettextprj(250));
	}
	else
		lcd.print(deltaEggMax / 10.0);


}

void DeltaEggClass::show()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(55));
	lcd.setCursor(0, 1);
	lcd.print(gettextprj(56));
	showMin();
	showMax();
}

void DeltaEggClass::refresh()
{
	if (bState[0] == btn_down && !appl[0])
	{
		_shift++;
		if (_shift >= 3)
		{
			_shift = 0;
		}
		EEPROM.update(20, deltaEggMin);
		EEPROM.update(21, deltaEggMax);
		appl[0] = true;
		_blinc = false;
		showMin();
		showMax();

	}
	else
	{
		if (_shift == 1)
		{
			float val = deltaEggMin;
			if (scrollBar(0, 100, 1, val))
			{
				deltaEggMin = val;

			}
		}
		else if (_shift == 2)
		{
			float val = deltaEggMax;
			if (scrollBar(0, 100, 1, val))
			{
				deltaEggMax = val;

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

		showMin();
		showMax();
	}


}


