// NodeChoseStart.h

#ifndef _NODECHOSESTART_h
#define _NODECHOSESTART_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"

class NodeChoseStartClass: public BaseNodeClass
{
	byte _max = 0;
	byte _shift = 0;
	bool _wait = false;
	byte _period = 0;
	byte _day = 0;
	byte _type = 0;

	bool _blinc = false;
	unsigned long _timer;
	void showData();
	
protected:
public:
	bool allowInner();
	bool allowOwner();
	bool allowNext();
	bool allowPrev();
	void show();
	void refresh();

};

#endif

