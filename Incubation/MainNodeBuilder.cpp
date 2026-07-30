//
//
//

#include "MainNodeBuilder.h"

#include "ChangeDisplayNode.h"
#include "DeltaEgg.h"
#include "DeltaLineNode.h"
#include "MinActionPercent.h"
#include "NodeChoseStart.h"
#include "function.h"
#include "node.h"
#include "objects.h"

template <typename TNode>
TNode *MainNodeBuilderClass::make() {
  TNode *node = new TNode();
  if (node != nullptr && _slot < MENU_SIZE) _listMenu[_slot++] = node;
  return node;
}

BaseNodeClass *MainNodeBuilderClass::closeSubmenu(BaseNodeClass *parent, BaseNodeClass **items,
                                                  byte count) {
  auto *exitNode = make<NodeClass>();
  if (exitNode == nullptr) return items[0];

  exitNode->Text[0] = Txt::Exit;
  exitNode->setOwner(parent);
  exitNode->setInner(parent);  // «Выход» возвращает на родительский экран

  for (byte i = 0; i < count; i++) {
    items[i]->setOwner(parent);  // ИСПРАВЛЕНО: часть узлов оставалась без Owner,
                                 // из-за чего кнопка «назад» на них не работала
    if (i > 0) link(items[i - 1], items[i]);
  }
  link(items[count - 1], exitNode);
  link(exitNode, items[0]);

  parent->setInner(items[0]);
  return items[0];
}

BaseNodeClass *MainNodeBuilderClass::buildMenu() {
  _slot = 0;

  // --- 1. Пороги аварийных режимов работы -------------------------------
  auto *alarms = make<NodeClass>();
  if (alarms == nullptr) return nullptr;
  alarms->Text[0] = Txt::AlarmSetup1;
  alarms->Text[1] = Txt::AlarmSetup2;

  auto *alarmTemp = make<DeltaLineNodeClass>();
  auto *alarmHum = make<DeltaLineNodeClass>();
  if (alarmTemp == nullptr || alarmHum == nullptr) return nullptr;
  alarmTemp->type = 0;  // температура
  alarmHum->type = 1;   // влажность
  BaseNodeClass *alarmItems[] = {alarmTemp, alarmHum};
  closeSubmenu(alarms, alarmItems, 2);

  // --- 2. Пороговые значения включения ----------------------------------
  auto *limits = make<NodeClass>();
  if (limits == nullptr) return alarms;
  limits->Text[0] = Txt::TrigVals1;
  limits->Text[1] = Txt::TrigVals2;

  auto *minPercent = make<MinActionPercentClass>();
  auto *eggDelta = make<DeltaEggClass>();
  if (minPercent == nullptr || eggDelta == nullptr) return alarms;
  BaseNodeClass *limitItems[] = {minPercent, eggDelta};
  closeSubmenu(limits, limitItems, 2);

  // --- 3. Дисплей --------------------------------------------------------
  auto *display = make<NodeClass>();
  if (display == nullptr) return alarms;
  display->Text[0] = Txt::Display;

  auto *displayEdit = make<ChangeDisplayNodeClass>();
  if (displayEdit == nullptr) return alarms;
  BaseNodeClass *displayItems[] = {displayEdit};
  closeSubmenu(display, displayItems, 1);

  // --- 4. Запуск цикла ---------------------------------------------------
  auto *start = make<NodeClass>();
  if (start == nullptr) return alarms;
  start->Text[0] = Txt::StartCycle1;
  start->Text[1] = Txt::StartCycle2;

  auto *startEdit = make<NodeChoseStartClass>();
  if (startEdit == nullptr) return alarms;
  BaseNodeClass *startItems[] = {startEdit};
  closeSubmenu(start, startItems, 1);

  // --- верхний уровень ---------------------------------------------------
  BaseNodeClass *top[] = {alarms, limits, display, start};
  return closeSubmenu(this, top, 4);
}

void MainNodeBuilderClass::show() { showTwoLines(Txt::MainMenu1, Txt::MainMenu2); }
