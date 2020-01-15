// 
// 
// 

#include "NodeManager.h"
#include "Alerting.h"
#include "objects.h"

NodeManagerClass NodeManager;

void NodeManagerClass::init()
{
	_currentnode = Menuconfig.initstatus();
	_mainnode = _currentnode;
}

void NodeManagerClass::work()
{
	for (byte i = 0; i < 4; i++)
	{
		if (bouncer[i].update())
		{
			adjustments.setup(BRITHPIN, CONTRPIN, bright, 100 - contr);
			_timing = millis();
			_timingsleep = _timing;
			appl[i] = false;

			if (bouncer[i].read() == HIGH)
			{
				bState[i] = btn_up;
			}
			else
			{
				bState[i] = btn_down;
				bPressTime[i] = millis();
			}
		}

		if (bState[i] == btn_down)
		{
			if (abs(millis() - bPressTime[i]) > PUSHINTERVAL)
			{
				_timing = millis();
				_timingsleep = _timing;
				bState[i] = btn_push;
				appl[i] = false;
			}
		}

	}

	if (bState[0] == btn_down)
		Alerting.BlockSound();

	if (bState[3] == btn_down && appl[3] == false)
	{
		if (_currentnode->getOwner() != NULL)
		{

			if (_currentnode->allowOwner())
			{
				_show = false;
				_currentnode = _currentnode->getOwner();
				bPressTime[3] = millis();
				appl[3] = true;
			}
		}
		else if (!appl[3])
		{
			_show = false;
			if (_status)
			{
				_currentnode = Menuconfig.initmenu();
				Menuconfig.clearstatus();
				_status = false;
			}
			else
			{
				_currentnode = Menuconfig.initstatus();
				Menuconfig.clearmenu();
				_status = true;
			}
			appl[3] = true;
		}

	}
	else if (bState[0] == btn_down && appl[0] == false)
	{

		if (_currentnode->getInner() != NULL)
		{

			if (_currentnode->allowInner())
			{
				_show = false;

				_currentnode = _currentnode->getInner();
				appl[0] = true;
			}
		}
		else if (_currentnode->exit && !_status)
		{

			_currentnode = Menuconfig.initstatus();
			Menuconfig.clearmenu();
			_status = true;
			_show = false;
			appl[0] = true;
		}
	}
	else if (bState[1] == btn_down && appl[1] == false)
	{


		if (_currentnode->getNext() != NULL)
		{

			if (_currentnode->allowNext())
			{
				_show = false;

				_currentnode = _currentnode->getNext();
				appl[1] = true;
			}
		}
	}
	else if (bState[2] == btn_down && appl[2] == false)
	{

		if (_currentnode->getPrev() != NULL)
		{
			if (_currentnode->allowPrev())
			{
				_show = false;

				_currentnode = _currentnode->getPrev();
				appl[2] = true;
			}
		}
	}

	if (abs(millis() - _timingsleep) > MENUEXIT || toroot)
	{
		toroot = false;
		if (!_status)
		{

			while (_currentnode->allowOwner() != NULL)
			{
				_currentnode = _currentnode->getOwner();
				_currentnode->show();
			}
			_currentnode = Menuconfig.initstatus();

			Menuconfig.clearmenu();
			_status = true;
			_show = false;
		}

		_timingsleep = millis();
		//adjustments.enterPowerSaving();
		adjustments.setup(BRITHPIN, CONTRPIN, 0, 100 - contr);
	}

	if (!_show)
	{
		_timing = millis();
		_currentnode->show();

		_show = true;
	}

	else
	{
		if (abs(millis() - _timing) > DISPLAYINTERVAL)
		{
			_currentnode = _mainnode;
			_show = false;
			/*if (_currentnode->autoinner)
			{
				if (_currentnode->getInner() != NULL)
				{
					if (_currentnode->allowInner())
					{
						_currentnode = _currentnode->getInner();
						
					}
				}
			}*/
		}
	}
	_currentnode->refresh();

}



