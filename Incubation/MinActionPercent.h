// MinActionPercent.h

#ifndef _MINACTIONPERCENT_h
#define _MINACTIONPERCENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"

class MinActionPercentClass: public BaseNodeClass
{
private:
	byte _shift = 0;
	bool _blinc = false;
	unsigned long _timer;
	void showHeat();
	void showHum();
protected:
public:
	bool allowInner();
	bool allowNext();
	bool allowPrev();
	void show();
	void refresh();
};


#endif

