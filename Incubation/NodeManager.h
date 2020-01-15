// NodeManager.h

#ifndef _NODEMANAGER_h
#define _NODEMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "node.h"
#include "menuconfig.h"

class NodeManagerClass
{
 private:
	 int test;
	 bool _status = true;
	 BaseNodeClass *_currentnode;
	 BaseNodeClass *_mainnode;
	 unsigned long _timing;
	 unsigned long _timingsleep;
	 bool _show = false;
	 
 protected:


 public:
	void init();
	void work();
};

extern NodeManagerClass NodeManager;

#endif


