// MainNodeBuilder.h

#ifndef _MAINNODEBUILDER_h
#define _MAINNODEBUILDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"

class MainNodeBuilderClass : public BaseNodeClass
{
private:
	BaseNodeClass  **_listMenu;
 public:
	 BaseNodeClass *getInner();

	 void show();
	 void deleteMenu();
};



#endif

