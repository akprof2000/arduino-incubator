//
// Общая реализация узла-владельца подменю.
//

#include "BaseNode.h"

#include "function.h"

BaseNodeClass *MenuOwnerNodeClass::getInner() {
  if (_listMenu != nullptr) return _listMenu[0];

  _listMenu = createListMenu(_menuSize);
  if (_listMenu == nullptr) return nullptr;  // не хватило кучи — остаёмся здесь

  BaseNodeClass *first = buildMenu();
  setInner(first);
  return first;
}

void MenuOwnerNodeClass::releaseMenu() {
  deleteListMenu(_menuSize, _listMenu);
  _listMenu = nullptr;
  setInner(nullptr);  // не оставляем висячий указатель
}
