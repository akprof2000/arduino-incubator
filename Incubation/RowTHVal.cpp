// 
// 
// 

#include "RowTHVal.h"
#include "function.h"
#include "consts.h"
#include "DataRow.h"
#include "objects.h"




void RowTHValClass::showTmp()
{
	lcd.setCursor(12, 0);
	if (_blinc && _shift == 1)
	{
		lcd.print(gettextprj(250));
	} else
		lcd.print(BASETEMP + _temp / 10.0, 1);
}

void RowTHValClass::showHum()
{
	lcd.setCursor(11, 1);
	if (_blinc && _shift == 2)
	{
		lcd.print(gettextprj(251));
	}
	else	
		lcd.print(BASEHUM + _hum);

}

bool RowTHValClass::allowInner()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}


bool RowTHValClass::allowNext()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}

bool RowTHValClass::allowPrev()
{
	if (_shift > 0 && _shift < 3)
	{
		return false;
	}
	else
		return true;
}

void RowTHValClass::show()
{
	DataRowClass *row = new DataRowClass();
	row->init(type, type1);
	_temp = row->GetTemp();
	_hum = row->GetHum();
	delete row;

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(20));
	lcd.setCursor(0, 1);
	lcd.print(gettextprj(21));
	showHum();
	showTmp();

}

void RowTHValClass::refresh()
{
	if (bState[0] == btn_down && !appl[0])
	{
		_shift++;
		if (_shift >= 3)
		{
			_shift = 0;
		}
	
		DataRowClass *row = new DataRowClass();
		row->init(type, type1);
		row->SetTemp(_temp);
		row->SetHum(_hum);
		row->save();
		delete row;

		appl[0] = true;
		_blinc = false;
		showHum();
		showTmp();

	}
	else
	{
		if (_shift == 1)
		{
			float val = _temp;
			if (scrollBar(0, 200, 1, val))
			{
				_temp = val;
				
				showHum();
				showTmp();

			}
		}
		else if (_shift == 2)
		{
			float val = _hum;
			if (scrollBar(0, 40, 1, val))
			{
				_hum = val;

				showHum();
				showTmp();

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
		showHum();
		showTmp();
	}
}
