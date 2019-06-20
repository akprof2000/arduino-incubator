// StatusMainInfo.h

#ifndef _STATUSMAININFO_h
#define _STATUSMAININFO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"

class StatusMainInfoClass: public BaseNodeClass
{
 protected:
	 bool _work;
	 bool _blink;
	 unsigned long _timer = 0;
 public:	 
	 bool allowInner();
	 bool allowNext();
	 bool allowPrev();
	 void show();
	 void refresh();
};



#endif

