// node.h

#ifndef _NODE_h
#define _NODE_h

#include <Arduino.h>

#include "BaseNode.h"
#include "consts.h"

// Простой статический экран из одной-двух строк текста (идентификаторы из texts.h).
class NodeClass : public BaseNodeClass {
 public:
  byte Text[LCDROWS] = {0, 0};  // БЫЛО: не инициализировалось -> мусор на экране
  void show() override;
};

#endif
