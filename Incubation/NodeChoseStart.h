// NodeChoseStart.h

#ifndef _NODECHOSESTART_h
#define _NODECHOSESTART_h

#include <Arduino.h>

#include "EditNode.h"

// Запуск цикла: выбор схемы, периода и дня старта.
// После прохода по всем трём полям экран переходит в режим ожидания
// подтверждения — длинное нажатие OK запускает цикл.
class NodeChoseStartClass : public EditNodeClass {
 public:
  NodeChoseStartClass() : EditNodeClass(3) {}
  void show() override;
  void refresh() override;
  // Пока ждём подтверждения, уход с экрана запрещён.
  bool allowOwner() override { return !_wait; }

 protected:
  void drawFields() override;
  void editField(byte field) override;
  byte nextField(byte current) const override;

 private:
  byte _maxDay = 0;
  byte _period = 0;
  byte _day = 0;
  byte _table = 0;
  bool _wait = false;

  void startCycle();
  void reloadMaxDay();
};

#endif
