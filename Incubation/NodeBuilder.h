// NodeBuilder.h

#ifndef _NODEBUILDER_h
#define _NODEBUILDER_h

#include <Arduino.h>

#include "BaseNode.h"

// Экран выбора вида птицы. Внутри — четыре периода схемы плюс «Выход».
class NodeBuilderClass : public MenuOwnerNodeClass {
 public:
  NodeBuilderClass() : MenuOwnerNodeClass(MENU_SIZE) {}
  void show() override;

 protected:
  BaseNodeClass *buildMenu() override;

 private:
  static constexpr byte MENU_SIZE = 5;
};

#endif
