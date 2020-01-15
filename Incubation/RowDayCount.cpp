// 
// 
// 

#include "RowDayCount.h"
#include "function.h"
#include "objects.h"


void RowDayCountClass::showCount()
{
	
	lcd.setCursor(7, 0);
	lcd.print(_from);
	
	lcd.setCursor(13, 0);
	if (_day == 0)
	{
		lcd.print(gettextprj(250));
	}
	else if (_from + _day - 1 < 10)
	{
		lcd.print(0);
		lcd.setCursor(14, 0);
	}

	if (_day != 0)
		lcd.print(_from + _day - 1);
	
	lcd.setCursor(8, 1);
	if (_blinc && _shift == 1)
	{
		lcd.print(gettextprj(250));
	}
	else
		lcd.print(_day);


}



bool RowDayCountClass::allowInner()
{
	if (_shift > 0 && _shift < 2)
	{
		return false;
	}
	else
		return true;
}


bool RowDayCountClass::allowNext()
{
	if (_shift > 0 && _shift < 2)
	{
		return false;
	}
	else
		return true;
}

bool RowDayCountClass::allowPrev()
{
	if (_shift > 0 && _shift < 2)
	{
		return false;
	}
	else
		return true;

}

void RowDayCountClass::show()
{
	DataRowClass *row = new DataRowClass();
	row->init(type, type1);	
	_day = row->GetDay();
	_from = row->GetFrom();
	delete row;

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(18));
	lcd.setCursor(0, 1);
	lcd.print(gettextprj(19));
	showCount();
}


void RowDayCountClass::refresh()
{
	
	if (bState[0] == btn_down && !appl[0])
	{
		_shift++;
		if (_shift >= 2)
		{
			_shift = 0;
		}

		DataRowClass *row = new DataRowClass();
		row->init(type, type1);
		row->SetDay(_day);
		row->save();
		delete row;


		appl[0] = true;
		_blinc = false;
		showCount();


	}
	else
	{
		if (_shift == 1)
		{
			float val = _day;
			if (scrollBar(0, 30, 1, val))
			{
				_day = val;
			}
		}

	}

	if (_shift > 0 && _shift < 2)
	{
		if (abs(millis() - _timer) > BLINKINTERVAL)
		{
			_timer = millis();
			_blinc = !_blinc;
		}

		showCount();
	}

}


