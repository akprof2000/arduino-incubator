// ChangeDisplayNode.h

#ifndef _CHANGEDISPLAYNODE_h
#define _CHANGEDISPLAYNODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"

class ChangeDisplayNodeClass: public BaseNodeClass
{
private:	
	byte _shift = 0;
	bool _blinc = false;
	unsigned long _timer;
	void showBr();
	void showCt();	
 protected:
 public:
	 bool allowInner();	 
	 bool allowNext();
	 bool allowPrev();
	 void show();
	 void refresh();
	
};



#endif

