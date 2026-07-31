// io.h
//
// Полярность выходов и управление исполнительными устройствами.
//
// Раньше уровни были зашиты прямо в код регуляторов: `digitalWrite(pin, HIGH)`
// означало «включить», а `analogWrite(pin, power)` — мощность напрямую.
// Это неверно для этого прибора: силовые ключи и опторазвязанные модули реле
// включаются НИЗКИМ уровнем. Уровни были раскиданы по двум десяткам мест
// в пяти файлах, поэтому ошибиться в одном из них было очень легко.
//
// Теперь полярность задана здесь и только здесь, а код регуляторов говорит
// «включить/выключить», а не «HIGH/LOW».

#ifndef _IO_h
#define _IO_h

#include <Arduino.h>

#include "consts.h"

// ---------------------------------------------------------------------------
// Уровень включения
// ---------------------------------------------------------------------------

// ТЭН (пин 2), вентилятор обдува (3), испаритель (4), реле лотка (17, 18):
// нагрузка включается НИЗКИМ уровнем.
constexpr bool POWER_ACTIVE_LOW = true;

// Светодиод и зуммер аварии (пины 5, 6) подключены напрямую к выводу
// и включаются высоким уровнем.
constexpr bool ALARM_ACTIVE_LOW = false;

// Уровень на выводе для заданного состояния нагрузки.
constexpr uint8_t levelFor(bool on, bool activeLow) {
  return (on != activeLow) ? HIGH : LOW;
}

// Скважность для ШИМ-выхода: при active-LOW нагрузка тем сильнее,
// чем МЕНЬШЕ значение на выводе.
constexpr uint8_t powerDuty(uint8_t power, bool activeLow) {
  return activeLow ? static_cast<uint8_t>(255 - power) : power;
}

// ---------------------------------------------------------------------------
// Полярность проверяется компилятором на каждой сборке — ошибиться в знаке
// при чтении кода легко, а цена ошибки здесь это невыключаемый ТЭН.
// ---------------------------------------------------------------------------
static_assert(levelFor(true, POWER_ACTIVE_LOW) == LOW,
              "Нагрузка должна включаться низким уровнем");
static_assert(levelFor(false, POWER_ACTIVE_LOW) == HIGH,
              "Нагрузка должна выключаться высоким уровнем");
static_assert(levelFor(true, ALARM_ACTIVE_LOW) == HIGH,
              "Сигнализация должна включаться высоким уровнем");
static_assert(levelFor(false, ALARM_ACTIVE_LOW) == LOW,
              "Сигнализация должна выключаться низким уровнем");

static_assert(powerDuty(0, POWER_ACTIVE_LOW) == 255,
              "Нулевая мощность = постоянный HIGH = ТЭН выключен");
static_assert(powerDuty(255, POWER_ACTIVE_LOW) == 0,
              "Полная мощность = постоянный LOW = ТЭН включён");
static_assert(powerDuty(64, POWER_ACTIVE_LOW) == 191, "Четверть мощности");

// Перевести вывод в выход, не «моргнув» нагрузкой.
//
// Важно для active-LOW: если сначала сделать pinMode(OUTPUT), вывод окажется
// в состоянии LOW, то есть нагрузка на мгновение ВКЛЮЧИТСЯ. Поэтому сначала
// выставляем безопасный уровень (для входа это включает подтяжку) и только
// потом переводим вывод в выход.
inline void initOutputSafe(uint8_t pin, bool activeLow) {
  digitalWrite(pin, levelFor(false, activeLow));
  pinMode(pin, OUTPUT);
  digitalWrite(pin, levelFor(false, activeLow));
}

// ---------------------------------------------------------------------------
// Исполнительные устройства
// ---------------------------------------------------------------------------

// ТЭН. Мощность 0..255, где 0 — выключен.
inline void heaterPower(uint8_t power) {
  analogWrite(HEATCONTROL, powerDuty(power, POWER_ACTIVE_LOW));
}

inline void heaterOff() { heaterPower(0); }

// Вентилятор обдува и вытяжки.
inline void coolerSet(bool on) { digitalWrite(COOLERPIN, levelFor(on, POWER_ACTIVE_LOW)); }

// Испаритель (увлажнение).
inline void evaporatorSet(bool on) { digitalWrite(FANPIN, levelFor(on, POWER_ACTIVE_LOW)); }

// Лоток: реле реверса. Одновременное включение обоих направлений исключено
// по построению — есть только три состояния.
inline void trayStop() {
  digitalWrite(TRAYLEFTPIN, levelFor(false, POWER_ACTIVE_LOW));
  digitalWrite(TRAYRIGHTPIN, levelFor(false, POWER_ACTIVE_LOW));
}

inline void trayMoveLeft() {
  digitalWrite(TRAYRIGHTPIN, levelFor(false, POWER_ACTIVE_LOW));
  digitalWrite(TRAYLEFTPIN, levelFor(true, POWER_ACTIVE_LOW));
}

inline void trayMoveRight() {
  digitalWrite(TRAYLEFTPIN, levelFor(false, POWER_ACTIVE_LOW));
  digitalWrite(TRAYRIGHTPIN, levelFor(true, POWER_ACTIVE_LOW));
}

// Аварийная индикация.
inline void alarmLedSet(bool on) { digitalWrite(ALARMLEDPIN, levelFor(on, ALARM_ACTIVE_LOW)); }
inline void alarmSoundSet(bool on) { digitalWrite(ALARMSOUNDPIN, levelFor(on, ALARM_ACTIVE_LOW)); }

// Все нагрузки в безопасное состояние (выключено). Вызывается в setup()
// до всего остального.
inline void actuatorsInitSafe() {
  initOutputSafe(HEATCONTROL, POWER_ACTIVE_LOW);
  initOutputSafe(COOLERPIN, POWER_ACTIVE_LOW);
  initOutputSafe(FANPIN, POWER_ACTIVE_LOW);
  initOutputSafe(TRAYLEFTPIN, POWER_ACTIVE_LOW);
  initOutputSafe(TRAYRIGHTPIN, POWER_ACTIVE_LOW);
  initOutputSafe(ALARMLEDPIN, ALARM_ACTIVE_LOW);
  initOutputSafe(ALARMSOUNDPIN, ALARM_ACTIVE_LOW);
}

#endif
