// MinActionPercent.h

#ifndef _MINACTIONPERCENT_h
#define _MINACTIONPERCENT_h

#include <Arduino.h>

#include "EditNode.h"

// Минимальные проценты включения нагрева и увлажнения.
class MinActionPercentClass : public EditNodeClass {
 public:
  MinActionPercentClass() : EditNodeClass(2) {}
  void show() override;

 protected:
  void drawFields() override;
  void editField(byte field) override;
  void commit() override;
};

#endif
