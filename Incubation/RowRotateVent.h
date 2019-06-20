// RowRotateVent.h

#ifndef _ROWROTATEVENT_h
#define _ROWROTATEVENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"

class RowRotateVentClass: public BaseNodeClass
{
	byte _rotate = 0;
	byte _vent = 0;
	byte _venttime = 0;
	byte _shift = 0;
	bool _blinc = false;
	bool _write = false;
	unsigned long _timer;
	void showRotate();
	void showVentilate();
 public:
	 bool allowInner();
	 
	 bool allowNext();
	 bool allowPrev();
	 void show();
	 void refresh();
};


#endif

