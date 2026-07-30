// MainNodeBuilder.h

#ifndef _MAINNODEBUILDER_h
#define _MAINNODEBUILDER_h

#include <Arduino.h>

#include "BaseNode.h"

// «Основное меню»: аварийные пороги, пороги включения, дисплей, запуск цикла.
class MainNodeBuilderClass : public MenuOwnerNodeClass {
 public:
  MainNodeBuilderClass() : MenuOwnerNodeClass(MENU_SIZE) {}
  void show() override;

 protected:
  BaseNodeClass *buildMenu() override;

 private:
  static constexpr byte MENU_SIZE = 15;

  // Индекс следующей свободной ячейки _listMenu при построении.
  byte _slot = 0;
  template <typename TNode>
  TNode *make();
  // Замыкает список `items` в кольцо и добавляет пункт «Выход» с возвратом
  // в `parent`.
  BaseNodeClass *closeSubmenu(BaseNodeClass *parent, BaseNodeClass **items, byte count);
};

#endif
