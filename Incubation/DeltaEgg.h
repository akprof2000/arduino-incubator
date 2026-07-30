// DeltaEgg.h

#ifndef _DELTAEGG_h
#define _DELTAEGG_h

#include <Arduino.h>

#include "EditNode.h"

// Пороги перегрева яйца относительно уставки (десятые доли °C).
class DeltaEggClass : public EditNodeClass {
 public:
  DeltaEggClass() : EditNodeClass(2) {}
  void show() override;

 protected:
  void drawFields() override;
  void editField(byte field) override;
  void commit() override;
};

#endif
