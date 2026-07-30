// RowDayCount.h

#ifndef _ROWDAYCOUNT_h
#define _ROWDAYCOUNT_h

#include <Arduino.h>

#include "EditNode.h"

// Длительность периода в днях и его границы в сквозной нумерации цикла.
class RowDayCountClass : public EditNodeClass {
 public:
  RowDayCountClass() : EditNodeClass(1) {}
  void show() override;

 protected:
  void drawFields() override;
  void editField(byte field) override;
  void commit() override;

 private:
  byte _from = 1;
  byte _day = 0;
};

#endif
