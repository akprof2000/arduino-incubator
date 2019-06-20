// VentilationControl.h

#ifndef _VENTILATIONCONTROL_h
#define _VENTILATIONCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum FanUser
{
	fu_hum,
	fu_temp,
	fu_vent,
	fu_none
};


class VentilationControlClass
{
	unsigned long _timer = 0;
	byte _currentVal = 0;
	float _delta = 255;
	bool _on = false;
	FanUser _curUser = fu_none;
 public:
	void SetSpeed(byte val, FanUser user);
	void wait();
	void refresh();
};

extern VentilationControlClass VentilationControl;

#endif

