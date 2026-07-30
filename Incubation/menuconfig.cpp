//
//
//

#include "menuconfig.h"

#include "AlertInfoNode.h"
#include "ControlSession.h"
#include "CurrentOperation.h"
#include "MainNodeBuilder.h"
#include "NodeBuilder.h"
#include "StatusMainInfo.h"
#include "TaskStatusInfo.h"
#include "TemperatureStatusInfo.h"
#include "function.h"
#include "objects.h"

MenuconfigClass Menuconfig;

void MenuconfigClass::clearmenu() {
  deleteListMenu(MENU_SIZE, _listMenu);
  _listMenu = nullptr;
}

void MenuconfigClass::clearstatus() {
  deleteListMenu(STATUS_SIZE, _listStatus);
  _listStatus = nullptr;
}

// ---------------------------------------------------------------------------
// Экраны статуса
// ---------------------------------------------------------------------------
BaseNodeClass *MenuconfigClass::initstatus() {
  clearstatus();  // защита от повторного вызова без освобождения (была утечка)

  currentRow.init(currentPeriod, currentTable);
  ControlSession.init();

  _listStatus = createListMenu(STATUS_SIZE);
  if (_listStatus == nullptr) return nullptr;

  _listStatus[0] = new StatusMainInfoClass();
  _listStatus[1] = new TemperatureStatusInfoClass();
  _listStatus[2] = new TaskStatusInfoClass();
  _listStatus[3] = new CurrentOperationClass();
  _listStatus[4] = new AlertInfoNodeClass();

  for (byte i = 0; i < STATUS_SIZE; i++) {
    if (_listStatus[i] == nullptr) {
      clearstatus();
      return nullptr;
    }
    _listStatus[i]->autoinner = true;
  }

  // Экраны статуса замкнуты в кольцо. Кнопка «OK» листает их по Inner
  // (как было раньше), а кнопки «вверх»/«вниз» — по Next/Prev.
  // Раньше Next/Prev не были связаны вовсе, и пролистать статус
  // можно было только одной кнопкой.
  for (byte i = 0; i < STATUS_SIZE; i++) {
    BaseNodeClass *next = _listStatus[(i + 1) % STATUS_SIZE];
    _listStatus[i]->setInner(next);
    BaseNodeClass::link(_listStatus[i], next);
  }

  return _listStatus[0];
}

// ---------------------------------------------------------------------------
// Экраны меню
// ---------------------------------------------------------------------------
BaseNodeClass *MenuconfigClass::initmenu() {
  clearmenu();

  _listMenu = createListMenu(MENU_SIZE);
  if (_listMenu == nullptr) return nullptr;

  auto *main = new MainNodeBuilderClass();
  auto *schemes = new NodeClass();
  auto *exitNode = new NodeClass();
  if (main == nullptr || schemes == nullptr || exitNode == nullptr) {
    delete main;
    delete schemes;
    delete exitNode;
    clearmenu();
    return nullptr;
  }

  _listMenu[0] = main;
  _listMenu[1] = schemes;
  _listMenu[2] = exitNode;

  schemes->Text[0] = Txt::SchemeSetup1;
  schemes->Text[1] = Txt::SchemeSetup2;

  exitNode->Text[0] = Txt::Exit;
  exitNode->exit = true;  // возврат к экранам статуса

  BaseNodeClass::link(main, schemes);
  BaseNodeClass::link(schemes, exitNode);
  BaseNodeClass::link(exitNode, main);

  buildSchemeMenu(schemes);

  return main;
}

void MenuconfigClass::buildSchemeMenu(BaseNodeClass *parent) {
  NodeBuilderClass *items[SCHEME_COUNT];

  for (byte i = 0; i < SCHEME_COUNT; i++) {
    auto *node = new NodeBuilderClass();
    if (node == nullptr) return;
    _listMenu[3 + i] = node;
    node->type = i;
    node->setOwner(parent);
    items[i] = node;
    if (i > 0) BaseNodeClass::link(items[i - 1], items[i]);
  }

  auto *exitNode = new NodeClass();
  if (exitNode == nullptr) return;
  _listMenu[3 + SCHEME_COUNT] = exitNode;
  exitNode->Text[0] = Txt::Exit;
  exitNode->setOwner(parent);
  exitNode->setInner(parent);

  BaseNodeClass::link(items[SCHEME_COUNT - 1], exitNode);
  BaseNodeClass::link(exitNode, items[0]);

  parent->setInner(items[0]);
}
