// Alerting.h

#ifndef _ALERTING_h
#define _ALERTING_h

#include <Arduino.h>

#include "texts.h"

enum AlertingType : uint8_t {
  at_connect = 0,  // дверь открыта слишком долго
  at_endplan = 1,  // план выполнен / цикл не запущен
  at_temp = 2,     // расхождение по температуре
  at_hum = 3,      // расхождение по влажности
  at_err = 4,      // отказ основного датчика
  at_count = 5
};

// Аварийная сигнализация: мигание светодиодом и звук.
class AlertingClass {
 public:
  void Start(AlertingType alert);
  void Finish(AlertingType alert);
  void Finish();          // погасить всё
  void SetWaitAllert();   // отложить звук после осознанного действия оператора
  void BlockSound();      // «квитировать» звук кнопкой
  void Print(TextBuilder &builder) const;
  void refresh();

  bool active() const { return _work; }

 private:
  bool _info[at_count] = {false, false, false, false, false};
  bool _blink = false;
  bool _work = false;
  bool _sound = false;
  unsigned long _timer = 0;
  unsigned long _wait = 0;
};

extern AlertingClass Alerting;

#endif
