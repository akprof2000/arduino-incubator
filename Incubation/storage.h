// storage.h
//
// Единая карта EEPROM. Раньше адреса были «размазаны» магическими числами
// по десятку файлов, из-за чего появился реальный баг: значение `timerUpdated`
// писалось по адресу 17, где уже хранился `currentHour` — они затирали
// друг друга. Теперь все адреса объявлены здесь и только здесь.

#ifndef _STORAGE_h
#define _STORAGE_h

#include <Arduino.h>

namespace Eeprom {
enum : int {
  Bright = 0,        // яркость подсветки, %
  Contrast = 1,      // контраст, %
  Magic = 2,         // признак «настройки проинициализированы»
  AlTmpDel = 3,      // порог включения нагрева, десятые доли °C
  AlTmpMax = 4,      // аварийное отклонение по температуре, °C
  AlHumDel = 5,      // порог включения увлажнения, %
  AlHumMax = 6,      // аварийное отклонение по влажности, %

  CurrentDay = 13,   // текущий день периода
  CurrentPeriod = 14,
  CurrentTable = 15, // текущая схема (вид птицы)
  Started = 16,      // цикл запущен
  CurrentHour = 17,

  MinHeat = 18,      // минимальный процент нагрева
  MinHum = 19,       // минимальный процент увлажнения
  DeltaEggMin = 20,  // перегрев яйца: нижний порог, десятые доли °C
  DeltaEggMax = 21,  // перегрев яйца: верхний порог, десятые доли °C

  TimerUpdated = 22, // БЫЛО 17 — конфликтовало с CurrentHour

  // Таблицы режимов: 6 схем x 4 периода x ROW_SIZE байт
  RowsBase = 0xFF
};

constexpr int RowSize = 9;      // байт на одну строку режима
constexpr uint8_t Tables = 6;   // видов птицы
constexpr uint8_t Periods = 4;  // периодов в схеме
constexpr uint8_t MagicValue = 1;

// Адрес поля `field` (0..RowSize-1) строки (table, period).
constexpr int rowAddr(uint8_t table, uint8_t period, uint8_t field) {
  return RowsBase + period * RowSize + table * RowSize * Periods + field;
}
}  // namespace Eeprom

// Записать байт настройки в EEPROM и одновременно взвести признак Magic.
// EEPROM.update() сам не перезаписывает ячейку, если значение не изменилось,
// поэтому ресурс EEPROM не расходуется впустую.
void saveSetting(int address, uint8_t value);

// Заполнить EEPROM заводскими таблицами режимов (используется при сбросе).
void writeFactoryTables();

#endif
