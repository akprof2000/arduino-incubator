// 
// 
// 

#include "DeltaLineNode.h"
#include "function.h"
#include "objects.h"
#include <EEPROM.h>


void DeltaLineNodeClass::showDTmp()
{
	lcd.setCursor(4, 1);
	if (_blinc && _shift == 1)
	{
		lcd.print(gettextprj(250));
	}
	else
		lcd.print(alTmpDel / 10.0);


}

void DeltaLineNodeClass::showMTmp()
{
	lcd.setCursor(14, 1);
	if (_blinc && _shift == 2)
	{
		lcd.print(gettextprj(251));
	}
	else
		lcd.print(alTmpMax);

}

void DeltaLineNodeClass::showDHum()
{
	lcd.setCursor(4, 1);
	if (_blinc && _shift == 1)
	{
		lcd.print(gettextprj(252));
	}
	else
		lcd.print(alHumDel);
}

void DeltaLineNodeClass::showMHum()
{
	lcd.setCursor(14, 1);
	if (_blinc && _shift == 2)
	{
		lcd.print(gettextprj(251));
	}
	else
		lcd.print(alHumMax);
}

bool DeltaLineNodeClass::allowInner()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;

}


bool DeltaLineNodeClass::allowNext()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}

bool DeltaLineNodeClass::allowPrev()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}

void DeltaLineNodeClass::show()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	if (type == 0)
		lcd.print(gettextprj(28));
	else
		lcd.print(gettextprj(30));
	lcd.setCursor(0, 1);
	if (type == 0)
		lcd.print(gettextprj(29));
	else
		lcd.print(gettextprj(31));
	if (type == 0)
	{
		showDTmp();
		showMTmp();
	}
	else
	{
		showDHum();
		showMHum();
	}
}


void DeltaLineNodeClass::refresh()
{
	if (bState[0] == btn_down && !appl[0])
	{
		_shift++;
		if (_shift >= 3)
		{
			_shift = 0;
		}
		if (type == 0)
		{
			EEPROM.update(3, alTmpDel);
			EEPROM.update(4, alTmpMax);
		}
		else
		{
			EEPROM.update(5, alHumDel);
			EEPROM.update(6, alHumMax);
		}
		EEPROM.update(2, 1);

		appl[0] = true;
		_blinc = false;
		if (type == 0)
		{
			showDTmp();
			showMTmp();
		}
		else
		{
			showDHum();
			showMHum();
		}

	}
	else
	{
		if (_shift == 1)
		{
			float val = 0;
			if (type == 0)
			{
				val = alTmpDel;
			} else
				val = alHumDel;

			if (scrollBar(1, type==0?99:30, 1, val))
			{

				if (type == 0)
				{
					alTmpDel = val;
				}
				else
				{
					alHumDel = val;
				}


			}
		}
		else if (_shift == 2)
		{
			float val = alTmpMax;
			if (type == 0)
			{
				val = alTmpMax;
			}
			else
				val = alHumMax;

			if (scrollBar(1, type==0?10:50, 1, val))
			{
				

				if (type == 0)
				{
					alTmpMax = val;
				}
				else
				{
					alHumMax = val;
				}

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

		if (type == 0)
		{
			showDTmp();
			showMTmp();
		}
		else
		{
			showDHum();
			showMHum();
		}
	}
}
