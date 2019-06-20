// DeltaLineNode.h

#ifndef _DELTALINENODE_h
#define _DELTALINENODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"

class DeltaLineNodeClass: public BaseNodeClass
{
	byte _shift = 0;
	bool _blinc = false;
	unsigned long _timer;
	void showDTmp();
	void showMTmp();
	void showDHum();
	void showMHum();
protected:
public:	
	bool allowInner();
	
	bool allowNext();
	bool allowPrev();
	void show();
	void refresh();
};



#endif

