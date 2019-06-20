// RowCooling.h

#ifndef _ROWCOOLING_h
#define _ROWCOOLING_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "node.h"


class RowCoolingClass : public BaseNodeClass
{
private:
	byte _count = 0;
	byte _time = 0;
	byte _temp = 0;
	bool _blinc;
	byte _shift;
	unsigned long _timer;
	void showCount();
	byte _from;
	byte _day;
	bool _write;
protected:
public:
	bool allowInner();
	
	bool allowNext();
	bool allowPrev();
	void show();
	void refresh();

};


#endif

