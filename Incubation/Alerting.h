// Alerting.h

#ifndef _ALERTING_h
#define _ALERTING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define ENUMALERTLENGTH 4

enum AlertingType
{
	at_connect,
	at_endplan,
	at_temp,
	at_hum
};

class AlertingClass
{
	bool _info[ENUMALERTLENGTH] = { false, false, false, false };
	bool _blink = false;
	bool _work = true;
	bool _sound = true;
	unsigned long _timer = 0;
	unsigned long _wait = 0;
 protected:


 public:
	 void SetWaitAllert();
	 void Start(AlertingType alert);
	 void Finish(AlertingType alert);
	 String Print();
	 void Finish();
	 void BlockSound();
	void refresh();
};

extern AlertingClass Alerting;

#endif

