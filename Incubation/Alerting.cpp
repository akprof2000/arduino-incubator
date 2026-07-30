//
//
//

#include "Alerting.h"

#include "consts.h"
#include "objects.h"
#include "timing.h"

AlertingClass Alerting;

void AlertingClass::Print(TextBuilder &builder) const {
  for (uint8_t i = 0; i < at_count; i++) {
    if (!_info[i]) continue;
    builder.addSeparator();
    builder.addP(Txt::AlertFirst + i);
  }

  // БЫЛО: разделитель "; " добавлялся к строке ДО проверки _info[i],
  // из-за чего первый же неактивный флаг сдвигал разделители
  // и строка начиналась с "; ".
  if (builder.empty()) builder.addP(Txt::NoDeviations);
}

void AlertingClass::Finish() {
  _sound = false;
  _work = false;
}

void AlertingClass::SetWaitAllert() {
  _wait = millis();
  if (_wait == 0) _wait = 1;  // 0 зарезервирован под «ожидания нет»
  _sound = false;
}

void AlertingClass::Start(AlertingType alert) {
  if (alert >= at_count) return;
  if (_info[alert]) return;

  _info[alert] = true;
  // Звук не включаем, пока действует «окно тишины» после действий оператора
  // (и первые WAITAFTEREVENT мс после включения прибора).
  if (expired(_wait, WAITAFTEREVENT)) _sound = true;
  _work = true;
}

void AlertingClass::Finish(AlertingType alert) {
  if (alert >= at_count) return;
  _info[alert] = false;

  for (uint8_t i = 0; i < at_count; i++) {
    if (_info[i]) return;  // осталась хотя бы одна авария
  }
  Finish();
}

void AlertingClass::BlockSound() {
  if (_wait == 0) _sound = false;
}

void AlertingClass::refresh() {
  if (_wait != 0 && expired(_wait, WAITAFTEREVENT)) {
    _sound = true;
    _wait = 0;
  }

  if (!expired(_timer, ERRORINTERVAL)) return;
  _timer = millis();

  if (_work) {
    _blink = !_blink;
  } else {
    _blink = false;
  }

  digitalWrite(ALARMLEDPIN, (_blink && _work) ? HIGH : LOW);
  digitalWrite(ALARMSOUNDPIN, (_blink && _work && _sound) ? HIGH : LOW);
}
