// initialize.h

#ifndef _INITIALIZE_h
#define _INITIALIZE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class InitializeClass
{
  private:
	int shift = 0;
	unsigned long timer = 0;

 public:
	bool init();
};

extern InitializeClass Initialize;

#endif




