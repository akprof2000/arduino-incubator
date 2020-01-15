// ControlSession.h

#ifndef _CONTROLSESSION_h
#define _CONTROLSESSION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Bounce2.h"
#include "consts.h"

struct timeshift
{
	bool min[24 * 60];
	bool skip;
};


class ControlSessionClass
{
	timeshift calculate(byte count);
	bool compare(timeshift data);
	Bounce door = Bounce(DOOREPIN, INTERVAL);
	Bounce center = Bounce(TRAYCENTERPIN, INTERVAL);
	bool _ventelate = false;
	bool _rotate = false;
	bool _rotchange = false;
	
	unsigned long _wait = 0;
	unsigned long _timmer = 0;
	unsigned long  _refreshtimmer = 0;
	unsigned long  _timerot = 0;
	unsigned long _timevent = 0;
	unsigned long _timefreze = 0;
	timeshift _delayvent;
	timeshift _rotation;
	
	bool _needrot = false;	
	bool _starting = false;
	unsigned long _timing;
 public:	 	 
	 bool Hum = true;
	 bool Heet = true;
	 void init();
	 void refresh();
};

extern ControlSessionClass ControlSession;

#endif

