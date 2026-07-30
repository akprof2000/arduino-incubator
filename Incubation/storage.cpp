//
// Работа с EEPROM: заводские таблицы режимов и сохранение настроек.
//

#include "storage.h"

#include <EEPROM.h>

#include "consts.h"

void saveSetting(int address, uint8_t value) {
  EEPROM.update(address, value);
  EEPROM.update(Eeprom::Magic, Eeprom::MagicValue);
}

// ---------------------------------------------------------------------------
// Заводские режимы инкубации.
//
// Раньше эти 24 строки были ~130 строками копипасты прямо в setup().
// Теперь это компактная таблица во FLASH (144 байта) и один цикл записи.
//
// Значения хранятся уже в «сыром» виде EEPROM:
//   temp = (°C - BASETEMP) * 10   (37.9 °C -> 79)
//   hum  = % - BASEHUM            (66 %   -> 21)
//
// Важно: в исходном коде пересчёт делался через float
// ((37.3 - 30) * 10 == 72.99999 -> усечение до 72), из-за чего часть
// уставок «съезжала» на 0.1 °C вниз. Здесь значения заданы точно.
// ---------------------------------------------------------------------------
struct FactoryRow {
  uint8_t day;       // длительность периода, дней
  uint8_t temp;      // (°C - 30) * 10
  uint8_t hum;       // % - 45
  uint8_t rotate;    // поворотов в сутки
  uint8_t vent;      // проветриваний в сутки
  uint8_t ventTime;  // длительность проветривания, мин
};

static const FactoryRow FACTORY[Eeprom::Tables][Eeprom::Periods] PROGMEM = {
    // Куры
    {{11, 79, 21, 4, 0, 0}, {6, 73, 8, 4, 4, 5}, {2, 73, 2, 4, 4, 20}, {2, 79, 21, 0, 4, 5}},
    // Индейка
    {{8, 80, 25, 4, 0, 0}, {4, 75, 15, 4, 2, 5}, {10, 72, 11, 4, 4, 20}, {3, 70, 25, 0, 2, 10}},
    // Утки
    {{16, 80, 15, 4, 2, 5}, {10, 75, 7, 4, 4, 20}, {2, 72, 25, 0, 2, 10}, {2, 70, 25, 0, 0, 0}},
    // Индоутки
    {{3, 78, 10, 4, 0, 0}, {8, 75, 7, 4, 2, 5}, {10, 72, 7, 4, 6, 20}, {2, 70, 25, 0, 2, 10}},
    // Гуси
    {{6, 78, 10, 4, 0, 0}, {8, 75, 7, 4, 2, 5}, {13, 72, 7, 4, 4, 20}, {2, 70, 25, 0, 2, 10}},
    // Перепела
    {{12, 76, 13, 4, 2, 5}, {4, 73, 8, 4, 2, 20}, {2, 72, 2, 0, 0, 0}, {2, 70, 21, 0, 0, 0}},
};

void writeFactoryTables() {
  for (uint8_t table = 0; table < Eeprom::Tables; table++) {
    for (uint8_t period = 0; period < Eeprom::Periods; period++) {
      const uint8_t *src = reinterpret_cast<const uint8_t *>(&FACTORY[table][period]);
      for (uint8_t field = 0; field < sizeof(FactoryRow); field++) {
        EEPROM.update(Eeprom::rowAddr(table, period, field), pgm_read_byte(src + field));
      }
    }
  }
}
