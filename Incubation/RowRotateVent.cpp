// 
// 
// 

#include "RowRotateVent.h"
#include "function.h"
#include "consts.h"
#include "DataRow.h"
#include "objects.h"


void RowRotateVentClass::showRotate()
{
	lcd.setCursor(8, 0);
	if (_blinc && _shift == 1)
	{	
		if (_rotate == 0)
			lcd.print(gettextprj(250));
		else
			lcd.print(gettextprj(251));
	}
	else
	{		
		if (_rotate == 0)
		{
			lcd.setCursor(0, 0);
			lcd.print(gettextprj(23));
			if (_shift == 1)
				_write = true;
		} 
		else
		{
			if (_write && _shift == 1)
			{
				_write = false;
				lcd.setCursor(0, 0);
				lcd.print(gettextprj(22));				
				lcd.setCursor(8, 0);
			}			
			
			lcd.print(_rotate);
		}

	}
}

void RowRotateVentClass::showVentilate()
{
	lcd.setCursor(4, 1);
	
	if (_blinc && _shift == 2)
	{
		if (_vent == 0)
			lcd.print(gettextprj(252));
		else
			lcd.print(gettextprj(251));
	}
	else
	{
		if (_vent == 0)
		{
			lcd.setCursor(0, 1);
			lcd.print(gettextprj(25));
			if (_shift == 2)
				_write = true;
		}
		else
		{
			if (_write && _shift == 2)
			{
				_write = false;
				lcd.setCursor(0, 1);
				lcd.print(gettextprj(24));
				lcd.setCursor(4, 1);
			}
			
			lcd.print(_vent);
		}
		
	}

	if (_vent != 0)
	{
		lcd.setCursor(13, 1);
		if (_blinc && _shift == 3)
		{
			lcd.print(gettextprj(251));
		}
		else
			lcd.print(_venttime);
	}
}

bool RowRotateVentClass::allowInner()
{
	if (_shift > 0 && _shift < 4)
	{
		return false;
	}
	else
		return true;
}


bool RowRotateVentClass::allowNext()
{
	
		if (_shift > 0 && _shift < 4)
		{
			return false;
		}
		else
			return true;
}

bool RowRotateVentClass::allowPrev()
{
	if (_shift > 0 && _shift < 4)
	{
		return false;
	}
	else
		return true;
}

void RowRotateVentClass::show()
{
	DataRowClass *row = new DataRowClass();
	row->init(type, type1);
	_rotate = row->GetRotate();
	_vent = row->GetVentCount();
	_venttime = row->GetVentTime();
	delete row;

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(22));
	lcd.setCursor(0, 1);
	lcd.print(gettextprj(24));
	showRotate();
	showVentilate();
}

void RowRotateVentClass::refresh()
{
	if (bState[0] == btn_down && !appl[0])
	{
		_shift++;
		if (_shift == 3 && _vent == 0)
			_shift++;
		if (_shift >= 4)
		{
			_shift = 0;
		}

		DataRowClass *row = new DataRowClass();
		row->init(type, type1);
		row->SetRotate(_rotate);
		row->SetVentCount(_vent);
		row->SetVentTime(_venttime);
		row->save();
		delete row;

		appl[0] = true;
		_blinc = false;
		showRotate();
		showVentilate();

	}
	else
	{
		if (_shift == 1)
		{
			float val = _rotate;
			if (scrollBar(0, 50, 1, val))
			{
				_rotate = val;
			}
		}
		else if (_shift == 2)
		{
			float val = _vent;
			if (scrollBar(0, 150, 1, val))
			{
				_vent = val;

			}
		}
		else if (_shift == 3)
		{
			float val = _venttime;
			if (scrollBar(3, 30, 1, val))
			{
				_venttime = val;
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
		showRotate();
		showVentilate();
	}
}
