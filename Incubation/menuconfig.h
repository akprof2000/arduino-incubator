// menuconfig.h

#ifndef _MENUCONFIG_h
#define _MENUCONFIG_h

#include <Arduino.h>

#include "node.h"

// Сборка двух деревьев экранов: «статус» (то, что видно всегда)
// и «меню» (настройки). В памяти одновременно живёт только одно из них.
class MenuconfigClass {
 public:
  BaseNodeClass *initmenu();
  BaseNodeClass *initstatus();
  void clearmenu();
  void clearstatus();

 private:
  // БЫЛО: указатели не инициализировались, а clearmenu() сразу вызывал
  // delete по мусору из SRAM.
  BaseNodeClass **_listMenu = nullptr;
  BaseNodeClass **_listStatus = nullptr;

  static constexpr byte MENU_SIZE = 10;
  static constexpr byte STATUS_SIZE = 5;
  static constexpr byte SCHEME_COUNT = 6;  // видов птицы

  void buildSchemeMenu(BaseNodeClass *parent);
};

extern MenuconfigClass Menuconfig;
#endif
