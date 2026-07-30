// HumidityControl.h

#ifndef _HUMIDITYCONTROL_h
#define _HUMIDITYCONTROL_h

#include <Arduino.h>

// Управление испарителем (увлажнение) и вытяжкой (осушение).
class HumidityControlClass {
 public:
  void wait();
  void refresh();

 private:
  unsigned long _timer = 0;
  double _delta = 255;
  bool _on = false;

  void dryControl();
};

extern HumidityControlClass HumidityControl;

#endif
