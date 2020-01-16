// CurrentOperation.h

#ifndef _CURRENTOPERATION_h
#define _CURRENTOPERATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "BaseNode.h"

class CurrentOperationClass: public BaseNodeClass
{	
	String _data = "";
	String _olddata = "--";
	unsigned long _time = 0;
	int pos = 0;
	
 public:
	void show();
	void refresh();
	void printLine(int refreshMSeconds);
};



#endif

