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
	byte _curr_hum = 0;
	byte _curr_temp = 0;
	byte _curr_vent = 0;
	byte _currentVal = 0;
	double _delta = 255;
	bool _on = false;
	FanUser _curUser = fu_none;
 public:
	void SetSpeed(double val, FanUser user);
	void wait();
	void refresh();
};

extern VentilationControlClass VentilationControl;

#endif

