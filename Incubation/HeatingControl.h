// HeatingControl.h

#ifndef _HEATINGCONTROL_h
#define _HEATINGCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class HeatingControlClass
{
	bool overHeating = false;
	void funcontrol();
 protected:


 public:
	 void wait();
	void refresh();
};

extern HeatingControlClass HeatingControl;

#endif

