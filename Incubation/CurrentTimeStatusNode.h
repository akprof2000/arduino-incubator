// CurrentTimeStatusNode.h

#ifndef _CURRENTTIMESTATUSNODE_h
#define _CURRENTTIMESTATUSNODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

	#include "node.h"

class CurrentTimeStatusNodeClass: public NodeClass {
 protected:
	 unsigned long _timer;
	 void showCurrentTime();
	 void showCurrentH();
	 void showCurrentY();
	 void strProgress(byte val);
 public:
	void init();
	void show();
	void refresh();
};



#endif


