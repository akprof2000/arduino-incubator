// StatusMainInfo.h

#ifndef _STATUSMAININFO_h
#define _STATUSMAININFO_h

#include <Arduino.h>

#include "BaseNode.h"

// Главный экран: уставки и текущие значения температуры и влажности.
// Пока цикл не запущен или отказал датчик — навигация по статусу
// заблокирована, экран показывает причину.
class StatusMainInfoClass : public BaseNodeClass {
 public:
  bool allowInner() override { return _work; }
  bool allowNext() override { return _work; }
  bool allowPrev() override { return _work; }
  void show() override;

 private:
  bool _work = false;
};

#endif
