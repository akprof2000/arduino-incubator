//
//
//

#include "NodeChoseStart.h"

#include <DS1307RTC.h>
#include <TimeLib.h>
#include <Wire.h>

#include "Alerting.h"
#include "ControlSession.h"
#include "DataRow.h"
#include "function.h"
#include "objects.h"
#include "storage.h"

byte NodeChoseStartClass::nextField(byte current) const { return current + 1; }

void NodeChoseStartClass::reloadMaxDay() {
  DataRowClass row;
  row.init(_period, _table);
  _maxDay = row.GetDay() > 0 ? row.GetDay() - 1 : 0;
  if (_day > _maxDay) _day = _maxDay;
}

void NodeChoseStartClass::show() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(T(Txt::StartCycle1));
  lcd.setCursor(0, 1);
  lcd.print(T(Txt::PeriodDay));
  drawFields();
}

void NodeChoseStartClass::drawFields() {
  lcd.setCursor(8, 0);
  if (hidden(1)) {
    lcd.print(T(Txt::Blank4));
    lcd.print(T(Txt::Blank4));
  } else {
    lcd.print(T(Txt::BirdFirst + _table));
    padTo(8 + TLen(Txt::BirdFirst + _table), 16);
  }

  lcd.setCursor(5, 1);
  if (hidden(2)) {
    lcd.print(T(Txt::Blank2));
  } else {
    lcd.print(_period + 1);
  }

  lcd.setCursor(13, 1);
  if (hidden(3)) {
    lcd.print(T(Txt::Blank3));
  } else {
    lcd.print(_day + 1);
    padTo(13 + (_day + 1 > 9 ? 2 : 1), 16);
  }
}

void NodeChoseStartClass::editField(byte field) {
  if (field == 1) {
    float val = _table;
    if (!scrollBar(0, Eeprom::Tables - 1, 1, val)) return;
    _table = static_cast<byte>(val);
    reloadMaxDay();  // у другой схемы другая длительность периода
  } else if (field == 2) {
    float val = _period;
    if (!scrollBar(0, Eeprom::Periods - 1, 1, val)) return;
    _period = static_cast<byte>(val);
    reloadMaxDay();
  } else {
    float val = _day;
    if (!scrollBar(0, _maxDay, 1, val)) return;
    _day = static_cast<byte>(val);
  }
}

void NodeChoseStartClass::refresh() {
  // Длинное нажатие OK в режиме ожидания = «запустить цикл».
  if (bState[BTN_OK] == btn_push && !appl[BTN_OK] && _wait) {
    appl[BTN_OK] = true;
    startCycle();
    return;
  }

  const byte before = _shift;
  EditNodeClass::refresh();

  if (_shift != before) {
    // Прошли последнее поле — ждём подтверждения запуска.
    _wait = (_shift == 0);
    if (_shift == 3) reloadMaxDay();
  }
}

void NodeChoseStartClass::startCycle() {
  currentDay = _day;
  currentPeriod = _period;
  currentTable = _table;
  started = 1;

  saveSetting(Eeprom::CurrentDay, currentDay);
  saveSetting(Eeprom::CurrentPeriod, currentPeriod);
  saveSetting(Eeprom::CurrentTable, currentTable);
  saveSetting(Eeprom::Started, started);

  setTime(0, 0, 0, currentDay + 1, 1, 2017);
  Alerting.Finish(at_endplan);

  if (RTC.chipPresent()) {
    timerUpdated = 1;
    RTC.set(now());
  } else {
    timerUpdated = 0;
  }
  // ИСПРАВЛЕНО: раньше timerUpdated записывался по адресу 17,
  // где хранится currentHour, — два значения затирали друг друга.
  saveSetting(Eeprom::TimerUpdated, timerUpdated);

  currentRow.init(currentPeriod, currentTable);
  ControlSession.init();

  _wait = false;
  bState[BTN_OK] = btn_up;

  showOneLine(Txt::StartCycle1);
  // БЫЛО: delay(3000) — три секунды прибор не реагировал ни на что,
  // включая сброс сторожевого таймера. Возврат в корень происходит
  // сразу, сообщение остаётся на экране до следующей перерисовки.
  toroot = true;
}
