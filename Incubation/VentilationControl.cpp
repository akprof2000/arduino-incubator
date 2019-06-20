// 
// 
// 

#include "VentilationControl.h"
#include "objects.h"



VentilationControlClass VentilationControl;

void VentilationControlClass::SetSpeed(byte val, FanUser user)
{	
	if (_curUser == user)
	{
		_currentVal = val;
	}
	else if (_currentVal < val )
	{
		_currentVal = val;
		_curUser = user;
	}
	
	_delta = (255.0 - _currentVal) * PEEKVALUE / PEEKDEV;
	
}

void VentilationControlClass::wait()
{
	digitalWrite(COOLERPIN, HIGH);
}

void VentilationControlClass::refresh()
{

	if (_currentVal > 0)
	{
		if (_currentVal >= 255 || _delta < PEEKVALUE)
		{
			digitalWrite(COOLERPIN, LOW);
			return;
		}
		if (_on)
		{
			if (abs(millis() - _timer) > PEEKVALUE)
			{
				_timer = millis();
				_on = false;
				digitalWrite(COOLERPIN, HIGH);
			}
		}
		else
		{
			if (abs(millis() - _timer) > _delta)
			{
				_timer = millis();
				_on = true;
				digitalWrite(COOLERPIN, LOW);
			}
		}


	}
	else
	{
		digitalWrite(COOLERPIN, HIGH);
	}

}

