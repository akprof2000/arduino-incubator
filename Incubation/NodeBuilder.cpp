//
//
//

#include "NodeBuilder.h"

#include "NodeTableBuilder.h"
#include "function.h"
#include "node.h"
#include "objects.h"
#include "storage.h"

BaseNodeClass *NodeBuilderClass::buildMenu() {
  // Четыре периода схемы...
  NodeTableBuilderClass *periods[Eeprom::Periods];
  for (byte i = 0; i < Eeprom::Periods; i++) {
    auto *node = new NodeTableBuilderClass();
    if (node == nullptr) return nullptr;
    _listMenu[i] = node;
    node->type = i;      // номер периода
    node->type1 = type;  // номер схемы (вида птицы)
    node->setOwner(this);
    periods[i] = node;
    if (i > 0) link(periods[i - 1], periods[i]);
  }

  // ...и пункт «Выход», замыкающий кольцо.
  auto *exitNode = new NodeClass();
  if (exitNode == nullptr) return periods[0];
  _listMenu[Eeprom::Periods] = exitNode;
  exitNode->Text[0] = Txt::Exit;
  exitNode->setOwner(this);
  exitNode->setInner(this);

  link(periods[Eeprom::Periods - 1], exitNode);
  link(exitNode, periods[0]);

  return periods[0];
}

void NodeBuilderClass::show() { showTwoLines(Txt::BirdFirst + type, Txt::Empty); }
