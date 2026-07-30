//
//
//

#include "DataRow.h"

#include <EEPROM.h>

#include "consts.h"
#include "storage.h"

void DataRowClass::init(uint8_t period, uint8_t table) {
  _period = period;
  _table = table;
  _from = 0;

  // БЫЛО: цикл for(i=0..8) со switch(i) внутри — восемь итераций ради
  // шести присваиваний. Читается напрямую.
  _day = EEPROM.read(Eeprom::rowAddr(_table, _period, 0));
  _temperature = EEPROM.read(Eeprom::rowAddr(_table, _period, 1));
  _humidity = EEPROM.read(Eeprom::rowAddr(_table, _period, 2));
  _rotation = EEPROM.read(Eeprom::rowAddr(_table, _period, 3));
  _ventilatecount = EEPROM.read(Eeprom::rowAddr(_table, _period, 4));
  _ventilatetime = EEPROM.read(Eeprom::rowAddr(_table, _period, 5));
}

void DataRowClass::save() const {
  EEPROM.update(Eeprom::rowAddr(_table, _period, 0), _day);
  EEPROM.update(Eeprom::rowAddr(_table, _period, 1), _temperature);
  EEPROM.update(Eeprom::rowAddr(_table, _period, 2), _humidity);
  EEPROM.update(Eeprom::rowAddr(_table, _period, 3), _rotation);
  EEPROM.update(Eeprom::rowAddr(_table, _period, 4), _ventilatecount);
  EEPROM.update(Eeprom::rowAddr(_table, _period, 5), _ventilatetime);
}

void DataRowClass::writeRow(uint8_t table, uint8_t period, uint8_t day, float temp, uint8_t hum,
                            uint8_t rot, uint8_t vent, uint8_t ventTime) {
  _table = table;
  _period = period;
  _day = day;
  // +0.5 — иначе float-арифметика даёт (37.3 - 30) * 10 == 72.99999
  // и усечение до 72 вместо 73.
  _temperature = static_cast<uint8_t>((temp - BASETEMP) * 10.0f + 0.5f);
  _humidity = hum - BASEHUM;
  _rotation = rot;
  _ventilatecount = vent;
  _ventilatetime = ventTime;
  _from = 0;
}

uint8_t DataRowClass::GetFrom() {
  if (_from != 0) return _from;

  // БЫЛО: в цикле создавался `new DataRowClass()` и тут же удалялся —
  // выделение в куче на каждой отрисовке экрана. Теперь объект на стеке.
  uint8_t total = 0;
  DataRowClass row;
  for (uint8_t i = 0; i < _period; i++) {
    row.init(i, _table);
    total += row.GetDay();
  }
  _from = total + 1;
  return _from;
}

float DataRowClass::TempCelsius() const { return _temperature / 10.0f + BASETEMP; }

uint8_t DataRowClass::HumidityPercent() const { return _humidity + BASEHUM; }
