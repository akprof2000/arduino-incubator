//
//
//

#include "VentilationControl.h"
#include "objects.h"



VentilationControlClass VentilationControl;

void VentilationControlClass::SetSpeed(double val, FanUser user)
{
	_curUser = user;
	_currentVal = 0;
	if (_curUser == fu_hum)
	{
		_curr_hum = round(val);
	}
	else if (_curUser == fu_temp)
	{
		_curr_temp = round(val);
	}
	else if (_curUser == fu_vent)
	{
		_curr_vent = round(val);
	}
	else
	{
		_currentVal = round(val);
	}


	byte cr = 0;

	if (cr < _curr_hum)
	{
		cr = _curr_hum;
	}

	if (cr < _curr_vent)
	{
		cr = _curr_vent;
	}

	if (cr < _curr_temp)
	{
		cr = _curr_temp;
	}

	_currentVal = cr;


	if (_curr_hum == 0 && _curr_temp == 0 && _curr_vent == 0)
	{
		_currentVal = 0;
	}
	else
	{
		_delta = (255.0 - _currentVal) * PEEKVALUE / PEEKDEV;
	}



}

void VentilationControlClass::wait()
{
	digitalWrite(COOLERPIN, LOW);
}

void VentilationControlClass::refresh()
{

	if (_currentVal > 0)
	{
//		lcd.setCursor(0, 0);
//		lcd.print("V=");
//		lcd.print(_currentVal);
		if (_currentVal >= 255 || _delta < PEEKVALUE)
		{
			digitalWrite(COOLERPIN, HIGH);
			return;
		}
		if (_on)
		{
			if (abs(millis() - _timer) > PEEKVALUE)
			{
				_timer = millis();
				_on = false;
				digitalWrite(COOLERPIN, LOW);

			}
		}
		else
		{
			if (abs(millis() - _timer) > _delta)
			{
				_timer = millis();
				_on = true;
				digitalWrite(COOLERPIN, HIGH);

			}
		}



	}
	else
	{
		digitalWrite(COOLERPIN, LOW);
//		lcd.setCursor(0, 0);
//		lcd.print("V=STOP");
	}

}

