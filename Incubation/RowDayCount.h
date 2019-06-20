// RowDayCount.h

#ifndef _ROWDAYCOUNT_h
#define _ROWDAYCOUNT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "node.h"


class RowDayCountClass: public BaseNodeClass
{
private:	
	bool _blinc;
	byte _shift;
	unsigned long _timer;
	void showCount();
	byte _from;
	byte _day;
protected:
public:
	bool allowInner();
	
	bool allowNext();
	bool allowPrev();
	void show();	
	void refresh();
	
};



#endif

