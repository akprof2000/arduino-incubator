// DeltaEgg.h

#ifndef _DELTAEGG_h
#define _DELTAEGG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"

class DeltaEggClass: public BaseNodeClass
{
private:
	byte _shift = 0;
	bool _blinc = false;
	unsigned long _timer;
	void showMin();
	void showMax();
protected:
public:
	bool allowInner();
	bool allowNext();
	bool allowPrev();
	void show();
	void refresh();
};


#endif

