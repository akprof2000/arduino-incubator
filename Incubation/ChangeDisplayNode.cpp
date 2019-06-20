// 
// 
// 
#include <EEPROM.h>
#include "ChangeDisplayNode.h"
#include "objects.h"
#include "function.h"

bool ChangeDisplayNodeClass::allowInner()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}



bool ChangeDisplayNodeClass::allowNext()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}

bool ChangeDisplayNodeClass::allowPrev()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;

}

void ChangeDisplayNodeClass::showBr()
{
	lcd.setCursor(9, 0);
	if (_blinc && _shift == 1)
	{
		lcd.print(gettextprj(252));
	}
	else
		lcd.print(bright);
	
	

}

void ChangeDisplayNodeClass::showCt()
{
	lcd.setCursor(10, 1);
	if (_blinc && _shift == 2)
	{
		lcd.print(gettextprj(252));
	}
	else
		lcd.print(contr);
	
	
}

void ChangeDisplayNodeClass::show()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(26));
	lcd.setCursor(0, 1);
	lcd.print(gettextprj(27));
	showBr();
	showCt();
}

void ChangeDisplayNodeClass::refresh()
{
	if (bState[0] == btn_down && !appl[0])
	{
		_shift++;
		if (_shift >= 3)
		{
			_shift = 0;
		}
		EEPROM.update(0, bright);
		EEPROM.update(1, contr);
		EEPROM.update(2, 1);

		appl[0] = true;
		_blinc = false;
		showBr();
		showCt();

	}
	else
	{
		if (_shift == 1)
		{
			float val = bright;
			if (scrollBar(0, 100, 1, val))
			{
				bright = val;
				adjustments.setup(BRITHPIN, CONTRPIN, bright, 100 - contr);
			}
		}
		else if (_shift == 2)
		{
			float val = contr;
			if (scrollBar(0, 100, 1, val))
			{
				contr = val;
				adjustments.setup(BRITHPIN, CONTRPIN, bright, 100 - contr);
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

		showBr();
		showCt();
	}


}


