// function.h

#ifndef _FUNCTION_h
#define _FUNCTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"	
#endif

	#include "BaseNode.h"
	String gettextprj(byte data);
	bool scrollBar(float minval, float maxval, float curstep, float &val);
	void baseShowData(int len, String str1, String str2);
	BaseNodeClass **createListMenu(byte size);
	void deleteListMenu(byte size, BaseNodeClass **listMenu) noexcept;
	int StrLength(String str);
#endif


