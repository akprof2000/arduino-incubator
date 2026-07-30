// RowTHVal.h

#ifndef _ROWTHVAL_h
#define _ROWTHVAL_h

#include <Arduino.h>

#include "EditNode.h"

// Уставки температуры и влажности для периода.
class RowTHValClass : public EditNodeClass {
 public:
  RowTHValClass() : EditNodeClass(2) {}
  void show() override;

 protected:
  void drawFields() override;
  void editField(byte field) override;
  void commit() override;

 private:
  byte _temp = 0;  // (°C - BASETEMP) * 10
  byte _hum = 0;   // % - BASEHUM
};

#endif
