// NodeTableBuilder.h

#ifndef _NODETABLEBUILDER_h
#define _NODETABLEBUILDER_h

#include <Arduino.h>

#include "BaseNode.h"

// Экран периода схемы. Внутри — редактирование длительности, уставок T/H,
// поворота и проветривания.
class NodeTableBuilderClass : public MenuOwnerNodeClass {
 public:
  NodeTableBuilderClass() : MenuOwnerNodeClass(MENU_SIZE) {}
  void show() override;

 protected:
  BaseNodeClass *buildMenu() override;

 private:
  static constexpr byte MENU_SIZE = 4;
};

#endif
