// node.h

#ifndef _NODE_h
#define _NODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "consts.h"
#include "BaseNode.h"

class NodeClass: public BaseNodeClass
{
 public:	 
	 byte Text[LCDROWS];	
	void show();
	
};


#endif


