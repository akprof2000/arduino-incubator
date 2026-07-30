// HeatingControl.h

#ifndef _HEATINGCONTROL_h
#define _HEATINGCONTROL_h

#include <Arduino.h>

// Управление ТЭНом и охлаждающим обдувом.
//
// Закон регулирования — квадратичный: мощность растёт как квадрат
// отклонения от уставки и достигает 100 % при отклонении alTmpMax.
// Ниже порога alTmpDel мощность не меняется (зона нечувствительности).
class HeatingControlClass {
 public:
  void wait();     // всё выключить (дверь открыта / цикл не идёт)
  void refresh();  // один шаг регулирования

 private:
  bool overHeating = false;  // яйцо перегрето — работаем на охлаждение
  void coolControl();
};

extern HeatingControlClass HeatingControl;

#endif
