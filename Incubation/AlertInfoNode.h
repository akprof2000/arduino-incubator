// AlertInfoNode.h

#ifndef _ALERTINFONODE_h
#define _ALERTINFONODE_h

#include <Arduino.h>

#include "ScrollTextNode.h"

// «Текущее событие»: список активных аварий.
class AlertInfoNodeClass : public ScrollTextNodeClass {
 public:
  AlertInfoNodeClass() : ScrollTextNodeClass(Txt::CurrentEvent) {}

 protected:
  void buildText(TextBuilder &builder) override;
};

#endif
