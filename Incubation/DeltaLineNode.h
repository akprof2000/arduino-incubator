// DeltaLineNode.h

#ifndef _DELTALINENODE_h
#define _DELTALINENODE_h

#include <Arduino.h>

#include "EditNode.h"

// Пороги регулирования и аварии.
//   type == 0 — температура, type == 1 — влажность.
class DeltaLineNodeClass : public EditNodeClass {
 public:
  DeltaLineNodeClass() : EditNodeClass(2) {}
  void show() override;

 protected:
  void drawFields() override;
  void editField(byte field) override;
  void commit() override;

 private:
  bool isTemperature() const { return type == 0; }
};

#endif
