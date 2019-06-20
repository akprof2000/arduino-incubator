// 
// 
// 

#include "DataRow.h"
#include "consts.h"
#include <EEPROM.h>

byte DataRowClass::GetFrom()
{
	if (_from != 0)
		return _from;

	for (byte i = 0; i < _gperiod; i++)
	{
		DataRowClass *dr = new DataRowClass();
		dr->init(i, _gtable);
		_from += dr->GetDay();
		delete dr;
	}
	_from++;
	return _from ;
}


void DataRowClass::writeRow(byte tbl, byte period, byte day, float temp, byte hum, byte rot, byte vent, byte ventt, byte cool, byte coolt, byte coolh)
{
	_gperiod = period;
	_gtable = tbl;

	_day = day;
	_temperature =  (temp  - BASETEMP) * 10;
	_humidity = hum - BASEHUM;
	_rotation = rot;
	_ventilatecount = vent;
	_ventilatetime = ventt;
	_cooling = cool;
	_coolingheat = coolh;
	_coolingtime = coolt;

}

void DataRowClass::save()
{

	for (byte i = 0; i < 9; i++)
	{

		switch (i)
		{
		case 0:

			EEPROM.update(0xFF + _gperiod * 9  + _gtable * 9 * 4 + 0, _day);
			break;
		case 1:
			EEPROM.update(0xFF + _gperiod * 9 + _gtable * 9 * 4 + 1, _temperature);
			break;
		case 2:

			EEPROM.update(0xFF + _gperiod * 9  + _gtable * 9 * 4 + 2, _humidity);
			break;
		case 3:
			EEPROM.update(0xFF + _gperiod * 9  + _gtable * 9 * 4 + 3, _rotation);
			break;
		case 4:
			EEPROM.update(0xFF + _gperiod * 9 + _gtable * 9 * 4 + 4, _ventilatecount);
			break;
		case 5:
			EEPROM.update(0xFF + _gperiod * 9  + _gtable * 9 * 4 + 5, _ventilatetime);
			break;
		case 6:
			EEPROM.update(0xFF + _gperiod * 9 + _gtable * 9 * 4 + 6, _cooling);
			break;
		case 7:
			EEPROM.update(0xFF + _gperiod * 9 + _gtable * 9 * 4 + 7, _coolingheat);
			break;
		case 8:
			EEPROM.update(0xFF + _gperiod * 9  + _gtable * 9 * 4 + 8, _coolingtime);
			break;

		default:
			break;
		}

	}

}

void DataRowClass::init(int period, int table)
{
	_gperiod = period;
	_gtable = table;

	for (byte i = 0; i < 9; i++)
	{

		switch (i)
		{
		case 0:
			_day = EEPROM.read(0xFF + _gperiod * 9  + _gtable * 9 * 4);
			break;
		case 1:
			_temperature = EEPROM.read(0xFF + _gperiod * 9 + _gtable * 9 * 4 + 1);
			break;
		case 2:
			_humidity = EEPROM.read(0xFF + _gperiod * 9 + _gtable * 9 * 4 + 2);
			break;
		case 3:
			_rotation = EEPROM.read(0xFF + _gperiod * 9 + _gtable * 9 * 4 + 3);
			break;
		case 4:
			_ventilatecount = EEPROM.read(0xFF + _gperiod * 9  + _gtable * 9 * 4 + 4);
			break;
		case 5:
			_ventilatetime = EEPROM.read(0xFF + _gperiod * 9 + _gtable * 9 * 4 + 5);
			break;
		case 6:
			_cooling = EEPROM.read(0xFF + _gperiod * 9  + _gtable * 9 * 4 + 6);
			break;
		case 7:
			_coolingheat = EEPROM.read(0xFF + _gperiod * 9  + _gtable * 9 * 4 + 7);
			break;
		case 8:
			_coolingtime = EEPROM.read(0xFF + _gperiod * 9  + _gtable * 9 * 4 + 8);
			break;

		default:
			break;
		}

	}


}

