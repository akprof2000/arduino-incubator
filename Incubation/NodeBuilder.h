// NodeBuilder.h

#ifndef _NODEBUILDER_h
#define _NODEBUILDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
	
#include "BaseNode.h"


class NodeBuilderClass: public BaseNodeClass
{
private:
	BaseNodeClass  **_listMenu;	
 protected:


 public:	 	 
	 BaseNodeClass *getInner();

	 void deleteMenu();

	 void show();

};



#endif

