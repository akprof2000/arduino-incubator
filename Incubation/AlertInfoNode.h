// AlertInfoNode.h

#ifndef _ALERTINFONODE_h
#define _ALERTINFONODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "BaseNode.h"

class AlertInfoNodeClass: public BaseNodeClass
{
	 String _data;
	 unsigned long _time = 0;
	 int pos = 0;

public:
	void show();
	void refresh();
	void printLine(int refreshMSeconds);
};



#endif

