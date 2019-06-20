// 
// 
// 

#include <EEPROM.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include "NodeChoseStart.h"
#include "objects.h"
#include "function.h"
#include "Alerting.h"
#include "ControlSession.h"

void NodeChoseStartClass::showData()
{
	lcd.setCursor(8, 0);
	if (_blinc && _shift == 1)
	{
		lcd.print(gettextprj(250));
		lcd.print(gettextprj(250));
		lcd.print(gettextprj(250));
	}
	else
	{
		lcd.print(gettextprj(12 + _type));
	}

	lcd.setCursor(5, 1);
	if (_blinc && _shift == 2)
	{
		lcd.print(gettextprj(251));
	}
	else
		lcd.print(_period + 1);

	lcd.setCursor(13, 1);
	if (_blinc && _shift == 3)
	{
		lcd.print(gettextprj(252));
	}
	else
		lcd.print(_day + 1);

}

bool NodeChoseStartClass::allowInner()
{
	if (_shift > 0 && _shift < 4)
	{
		return false;
	}
	else
		return true;
}

bool NodeChoseStartClass::allowOwner()
{
	if (_wait)
	{
		return false;
	}
	else
		return true;
}

bool NodeChoseStartClass::allowNext()
{
	if (_shift > 0 && _shift < 4)
	{
		return false;
	}
	else
		return true;
}

bool NodeChoseStartClass::allowPrev()
{
	if (_shift > 0 && _shift < 4)
	{
		return false;
	}
	else
		return true;
}

void NodeChoseStartClass::show()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(gettextprj(10));
	lcd.setCursor(0, 1);
	lcd.print(gettextprj(7));
	showData();

}

void NodeChoseStartClass::refresh()
{
	if (bState[0] == btn_push && !appl[0] && _wait)
	{
		currentDay = _day;
		currentPeriod = _period;
		currentTable = _type;

		EEPROM.update(13, currentDay);
		EEPROM.update(14, currentPeriod);
		EEPROM.update(15, currentTable);
		started = 1;
		EEPROM.update(16, started);


		setTime(0, 0, 0, currentDay + 1, 1, 2017);
		time_t t = now();
		Alerting.Finish(at_endplan);
		if (RTC.chipPresent()) {
			timerUpdated = 1;
			RTC.set(t);   // set the RTC and the system time to the received value			
		}
		else
			timerUpdated = 0;
		EEPROM.update(17, timerUpdated);


		currentRow.init(currentPeriod, currentTable);
		ControlSession.init();
		appl[0] = true;
		_wait = false;

		bState[0] = btn_up;

		baseShowData(1, gettextprj(10), gettextprj(0));

		delay(3000);
		toroot = true;
		return;
	}

	if (bState[0] == btn_down && !appl[0])
	{
		_wait = false;
		_shift++;
		if (_shift >= 4)
		{
			_wait = true;
			_shift = 0;
		}

		if (_shift == 3)
		{
			DataRowClass *row = new DataRowClass();
			row->init(_period, _type);
			_max = row->GetDay() - 1;
			delete row;
			if (_day > _max)
				_day = _max;

		}
		appl[0] = true;
		_blinc = false;
		showData();


	}
	else
	{
		if (_shift == 1)
		{
			float val = _type;
			if (scrollBar(0, 5, 1, val))
			{
				_type = val;

			}
		}
		else if (_shift == 2)
		{
			float val = _period;
			if (scrollBar(0, 3, 1, val))
			{
				_period = val;

			}
		}
		else if (_shift == 3)
		{
			float val = _day;
			if (scrollBar(0, _max, 1, val))
			{
				_day = val;

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

		showData();

	}
}
