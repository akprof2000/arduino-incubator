//
//
//

#include "NodeTableBuilder.h"

#include "RowDayCount.h"
#include "RowRotateVent.h"
#include "RowTHVal.h"
#include "function.h"
#include "node.h"
#include "objects.h"

BaseNodeClass *NodeTableBuilderClass::buildMenu() {
  auto *days = new RowDayCountClass();
  auto *values = new RowTHValClass();
  auto *rotate = new RowRotateVentClass();
  auto *exitNode = new NodeClass();

  if (days == nullptr || values == nullptr || rotate == nullptr || exitNode == nullptr) {
    delete days;
    delete values;
    delete rotate;
    delete exitNode;
    return nullptr;
  }

  _listMenu[0] = days;
  _listMenu[1] = values;
  _listMenu[2] = rotate;
  _listMenu[3] = exitNode;

  for (byte i = 0; i < 3; i++) {
    _listMenu[i]->type = type;    // период
    _listMenu[i]->type1 = type1;  // схема
    _listMenu[i]->setOwner(this);
  }

  exitNode->Text[0] = Txt::Exit;
  exitNode->setOwner(this);
  exitNode->setInner(this);

  link(days, values);
  link(values, rotate);
  link(rotate, exitNode);
  link(exitNode, days);

  return days;
}

void NodeTableBuilderClass::show() {
  // ВАЖНО: раньше show() сам вызывал deleteListMenu(), оставляя _Inner
  // висячим указателем на освобождённую память. Освобождением подменю
  // теперь занимается NodeManager (deleteMenu() перед каждым show()).
  showTwoLines(Txt::BirdFirst + type1, Txt::PeriodFirst + type);
}
