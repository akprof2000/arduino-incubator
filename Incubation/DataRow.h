// DataRow.h

#ifndef _DATAROW_h
#define _DATAROW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DataRowClass
{
private:
	byte _day;
	byte _temperature;
	byte _humidity;
	byte _rotation;
	byte _ventilatecount;
	byte _ventilatetime;
	byte _period;
	byte _gperiod;
	byte _gtable;
	byte _from;

public:
	byte GetFrom();
	byte GetDay() { return _day; };
	void SetDay(byte day) { _day = day; };
	byte GetTemp() { return _temperature; };
	byte GetRotate() { return _rotation; };
	byte GetVentCount() { return _ventilatecount; };
	byte GetVentTime() { return _ventilatetime; };
	byte GetHum() { return _humidity; };
	void SetTemp(byte temperature) { _temperature = temperature; };
	void SetRotate(byte rotate) { _rotation = rotate; };
	void SetVentCount(byte count) { _ventilatecount = count; };
	void SetVentTime(byte time) { _ventilatetime= time; };
	void SetHum(byte humidity) { _humidity = humidity; };
	void writeRow(byte tbl, byte period, byte day, float  temp, byte hum, byte rot, byte vent, byte ventt);

	void save();
	void init(int period, int table);
};

#endif


