// DataRow.h

#ifndef _DATAROW_h
#define _DATAROW_h

#include <Arduino.h>

// Одна строка режима инкубации: длительность периода и уставки.
// Значения хранятся в «сыром» виде EEPROM (см. storage.h).
class DataRowClass {
 public:
  // БЫЛО: у класса не было конструктора, поля (в том числе кэш `_from`)
  // содержали мусор из SRAM. GetFrom() проверял `if (_from != 0)`
  // и возвращал случайное число.
  DataRowClass() = default;

  void init(uint8_t period, uint8_t table);
  void save() const;
  void writeRow(uint8_t table, uint8_t period, uint8_t day, float temp, uint8_t hum,
                uint8_t rot, uint8_t vent, uint8_t ventTime);

  // Номер первого дня этого периода в сквозной нумерации цикла.
  uint8_t GetFrom();

  uint8_t GetDay() const { return _day; }
  uint8_t GetTemp() const { return _temperature; }
  uint8_t GetHum() const { return _humidity; }
  uint8_t GetRotate() const { return _rotation; }
  uint8_t GetVentCount() const { return _ventilatecount; }
  uint8_t GetVentTime() const { return _ventilatetime; }

  void SetDay(uint8_t day) { _day = day; }
  void SetTemp(uint8_t temperature) { _temperature = temperature; }
  void SetHum(uint8_t humidity) { _humidity = humidity; }
  void SetRotate(uint8_t rotate) { _rotation = rotate; }
  void SetVentCount(uint8_t count) { _ventilatecount = count; }
  void SetVentTime(uint8_t time) { _ventilatetime = time; }

  // Уставка температуры в °C.
  float TempCelsius() const;
  // Уставка влажности в %.
  uint8_t HumidityPercent() const;

 private:
  uint8_t _day = 0;
  uint8_t _temperature = 0;
  uint8_t _humidity = 0;
  uint8_t _rotation = 0;
  uint8_t _ventilatecount = 0;
  uint8_t _ventilatetime = 0;
  uint8_t _period = 0;
  uint8_t _table = 0;
  uint8_t _from = 0;  // кэш GetFrom(); 0 — ещё не посчитан
};

#endif
