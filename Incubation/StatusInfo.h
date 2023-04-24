// StatusInfo.h

#ifndef _STATUSINFO_h
#define _STATUSINFO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#define STATLEN 9

enum StatusOper
{
	so_none = 0,
	so_blow = 1,
	so_heet = 2,
	so_cool = 3,
	so_wet = 4,
	so_dry = 5,
	so_rot = 6,
	so_cent = 7,
	so_door = 8
};


class StatusInfoClass
{
	byte _oper[STATLEN];
 protected:


 public:
	 StatusInfoClass()
	 {
		 for (size_t i = 0; i < STATLEN; i++)
		 {
			 _oper[i] = 0;
		 }
	 }
	 void AddStatus(StatusOper status, double fill);
	 String Print();
};

extern StatusInfoClass StatusInfo;

#endif

