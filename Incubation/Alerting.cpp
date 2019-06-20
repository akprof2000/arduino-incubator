// 
// 
// 

#include "Alerting.h"
#include "consts.h"
#include "objects.h"
#include "function.h"

AlertingClass Alerting;

String AlertingClass::Print()
{
	byte len = 0;
	String res = "";
	for (size_t i = 0; i < ENUMALERTLENGTH; i++)
	{
		String curr = len > 0 ? "; " : "";		


		curr += gettextprj(150 + i);
		
		if (_info[i])
		{
			res += curr;
			len++;
		}
	}

	if (len == 0)
		res = gettextprj(111);

	return res;
}
void AlertingClass::Finish()
{
	_sound = false;
	_work = false;
}

void AlertingClass::SetWaitAllert()
{
	_wait = millis();
	_sound = false;
}

void AlertingClass::Start(AlertingType alert)
{
	if (!_info[(int)alert])
	{
		_info[(int)alert] = true;
		if (abs(millis() - _wait) > WAITAFTEREVENT)
			_sound = true;
		_work = true;
	}

}

void AlertingClass::Finish(AlertingType alert)
{
	if (_info[(int)alert])
	{
		_info[(int)alert] = false;
	}

	bool alrt = false;
	for (size_t i = 0; i < ENUMALERTLENGTH; i++)
	{
		if (_info[i])
		{
			alrt = true;
		}
	}
	if (!alrt)
	{
		Finish();
	}
}

void AlertingClass::BlockSound()
{
	if (_wait == 0)
		_sound = false;
}

void AlertingClass::refresh()
{
	
	
	if (_wait != 0)
	{
		if (abs(millis() - _wait) > WAITAFTEREVENT)
		{
			_sound = true;
			_wait = 0;
		}	
	}

	if (abs(millis() - _timer) < ERRORINTERVAL)
	{
		return;
	}
	_timer = millis();

	if (_work)
	{
		_blink = !_blink;
	}
	digitalWrite(ALARMLEDPIN, _blink && _work ? HIGH : LOW);
	digitalWrite(ALARMSOUNDPIN, _blink && _work  && _sound ? HIGH : LOW);

}
