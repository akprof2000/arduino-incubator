// NodeTableBuilder.h

#ifndef _NODETABLEBUILDER_h
#define _NODETABLEBUILDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"


class NodeTableBuilderClass : public BaseNodeClass
{
private:
	BaseNodeClass  **_listMenu;	

 public:
	 BaseNodeClass *getInner();
	 void show();

};



#endif

