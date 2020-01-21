// menuconfig.h

#ifndef _MENUCONFIG_h
#define _MENUCONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
	#include "node.h"
	

class MenuconfigClass
{
private:
	//void shema(BaseNodeClass *node, int ind, int period );
	BaseNodeClass  **_listMenu;
	BaseNodeClass **_listStatus;	
	void shememenu(BaseNodeClass *node);
 protected:	 
	 

 public:
	 BaseNodeClass *initmenu();
	void clearmenu();
	void clearstatus();
	BaseNodeClass *initstatus();
};

extern MenuconfigClass Menuconfig;
#endif
