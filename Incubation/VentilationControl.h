// VentilationControl.h

#ifndef _VENTILATIONCONTROL_h
#define _VENTILATIONCONTROL_h

#include <Arduino.h>

// Кто именно запросил обдув. Итоговая скорость — максимум из запросов,
// чтобы увлажнение, охлаждение и плановое проветривание не «спорили»
// за один вентилятор.
enum FanUser : uint8_t { fu_hum, fu_temp, fu_vent, fu_none };

// Вентилятор управляется «медленным» ШИМ с периодом PEEKVALUE:
// обычный analogWrite на такой нагрузке даёт гудение и не даёт тяги
// на малых значениях.
class VentilationControlClass {
 public:
  void SetSpeed(double val, FanUser user);
  void wait();
  void refresh();

 private:
  unsigned long _timer = 0;
  byte _curr_hum = 0;
  byte _curr_temp = 0;
  byte _curr_vent = 0;
  byte _currentVal = 0;
  double _delta = 255;  // длительность паузы, мс
  bool _on = false;
};

extern VentilationControlClass VentilationControl;

#endif
