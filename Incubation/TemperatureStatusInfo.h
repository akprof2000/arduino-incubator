// TemperatureStatusInfo.h

#ifndef _TEMPERATURESTATUSINFO_h
#define _TEMPERATURESTATUSINFO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BaseNode.h"
#include <OneWire.h>
#include <DallasTemperature.h>



class TemperatureStatusInfoClass: public BaseNodeClass
{
	float _max, _min;
	class address
	{
	public:
		DeviceAddress addr;
	} **lDev;
	void printTemp(byte ind);
	

 public:
	 TemperatureStatusInfoClass();
	 ~TemperatureStatusInfoClass();
	 void show();
	
};



#endif

