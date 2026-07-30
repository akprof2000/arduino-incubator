// CurrentOperation.h

#ifndef _CURRENTOPERATION_h
#define _CURRENTOPERATION_h

#include <Arduino.h>

#include "ScrollTextNode.h"

// «Текущая операция»: что прямо сейчас делают исполнительные устройства.
class CurrentOperationClass : public ScrollTextNodeClass {
 public:
  CurrentOperationClass() : ScrollTextNodeClass(Txt::CurrentOp) {}

 protected:
  void buildText(TextBuilder &builder) override;
};

#endif
