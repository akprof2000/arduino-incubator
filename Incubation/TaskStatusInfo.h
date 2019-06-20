// TaskStatusInfo.h

#ifndef _TASKSTATUSINFO_h
#define _TASKSTATUSINFO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "BaseNode.h"

class TaskStatusInfoClass: public BaseNodeClass
{
 public:
	void show();
};



#endif

