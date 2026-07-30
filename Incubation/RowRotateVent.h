// RowRotateVent.h

#ifndef _ROWROTATEVENT_h
#define _ROWROTATEVENT_h

#include <Arduino.h>

#include "EditNode.h"

// Поворот лотка и проветривание: сколько раз в сутки и по сколько минут.
class RowRotateVentClass : public EditNodeClass {
 public:
  RowRotateVentClass() : EditNodeClass(3) {}
  void show() override;

 protected:
  void drawFields() override;
  void editField(byte field) override;
  void commit() override;
  // Если проветривание выключено, поле «длительность» пропускается.
  byte nextField(byte current) const override;

 private:
  byte _rotate = 0;    // поворотов в сутки
  byte _vent = 0;      // проветриваний в сутки
  byte _venttime = 0;  // минут на одно проветривание
};

#endif
