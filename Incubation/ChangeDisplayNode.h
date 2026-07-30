// ChangeDisplayNode.h

#ifndef _CHANGEDISPLAYNODE_h
#define _CHANGEDISPLAYNODE_h

#include <Arduino.h>

#include "EditNode.h"

// Яркость подсветки и контраст.
class ChangeDisplayNodeClass : public EditNodeClass {
 public:
  ChangeDisplayNodeClass() : EditNodeClass(2) {}
  void show() override;

 protected:
  void drawFields() override;
  void editField(byte field) override;
  void commit() override;
};

#endif
