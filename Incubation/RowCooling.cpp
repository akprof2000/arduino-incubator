// 
// 
// 

#include "RowCooling.h"

#include "function.h"
#include "objects.h"

void RowCoolingClass::showCount()
{

	lcd.setCursor(4, 0);
	if (_blinc && _shift == 1)
	{
		if (_count == 0)
			lcd.print(gettextprj(250));
		else
			lcd.print(gettextprj(251));
	}
	else
	{
		if (_count == 0)
		{
			if (!_write)
			{
				lcd.clear();
			}
				lcd.setCursor(0, 0);
				lcd.print(gettextprj(38));
			
			if (_shift == 1)
				_write = true;
		}
		else
		{
			if (_write && _shift == 1)
			{
				_write = false;
				lcd.setCursor(0, 0);
				lcd.print(gettextprj(36));
				lcd.setCursor(0, 1);
				lcd.print(gettextprj(37));

				lcd.setCursor(4, 0);
			}

			lcd.print(_count);
		}
	}

	if (_count > 0)
	{
		lcd.setCursor(13, 0);
		if (_blinc && _shift == 2)
		{
			lcd.print(gettextprj(251));
		}
		else
		{
			lcd.print(_time);
		}

		lcd.setCursor(8, 1);
		if (_blinc && _shift == 3)
		{
			lcd.print(gettextprj(251));
		}
		else
		{
			lcd.print(_temp);
		}

	}
}

bool RowCoolingClass::allowInner()
{
	if (_shift > 0 && _shift < 4)
	{
		return false;
	}
	else
		return true;
}


bool RowCoolingClass::allowNext()
{
	if (_shift > 0 && _shift < 4)
	{
		return false;
	}
	else
		return true;
}

bool RowCoolingClass::allowPrev()
{
	if (_shift > 0 && _shift < 4)
	{
		return false;
	}
	else
		return true;
}

void RowCoolingClass::show()
{
	DataRowClass *row = new DataRowClass();
	row->init(type, type1);
	_count = row->GetCoolCount();
	_time = row->GetCoolTime();
	_temp = row->GetCoolHeat();
	delete row;

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(36));
	lcd.setCursor(0, 1);
	lcd.print(gettextprj(37));
	showCount();

}

void RowCoolingClass::refresh()
{

	if (bState[0] == btn_down && !appl[0])
	{
		_shift++;
		if (_shift == 2 && _count == 0)
			_shift++;
		if (_shift == 3 && _count == 0)
			_shift++;
		if (_shift >= 4)
		{
			_shift = 0;
		}

		DataRowClass *row = new DataRowClass();
		row->init(type, type1);
		row->SetCoolCount(_count);
		row->SetCoolHeat(_temp);
		row->SetCoolTime(_time);
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
			float val = _count;
			if (scrollBar(0, 24, 1, val))
			{
				_count = val;
			}
		}
		else if (_shift == 2)
		{
			float val = _time;
			if (scrollBar(5, 20, 1, val))
			{
				_time = val;

			}
		}
		else if (_shift == 3)
		{
			float val = _temp;
			if (scrollBar(25, 50, 1, val))
			{
				_temp = val;
			}
		}

	}

	if (_shift > 0 && _shift < 4)
	{
		if (abs(millis() - _timer) > BLINKINTERVAL)
		{
			_timer = millis();
			_blinc = !_blinc;
		}
		showCount();
	}
}
