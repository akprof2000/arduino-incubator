// RowTHVal.h

#ifndef _ROWTHVAL_h
#define _ROWTHVAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"

class RowTHValClass: public BaseNodeClass
{
	byte _shift = 0;
	byte _hum = 0;
	byte _temp = 0;
	bool _blinc = false;
	unsigned long _timer;
	void showTmp();
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

