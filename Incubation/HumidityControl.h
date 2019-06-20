// HumidityControl.h

#ifndef _HUMIDITYCONTROL_h
#define _HUMIDITYCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class HumidityControlClass
{	
	unsigned long _timer = 0;
	byte _currentVal = 0;
	float _delta = 255;
	bool _on = false;
 
 public:
	
	 void funcontrol();
	 void wait();
	 void refresh();
};

extern HumidityControlClass HumidityControl;

#endif

