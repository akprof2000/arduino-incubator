// BaseNode.h
//
// Узел меню. Экраны связаны в четыре стороны:
//   Prev/Next  — соседние пункты одного уровня (кольцевой список),
//   Inner      — вложенный экран («вход»),
//   Owner      — родительский экран («выход»).

#ifndef _BASENODE_h
#define _BASENODE_h

#include <Arduino.h>

class BaseNodeClass {
 protected:
  BaseNodeClass *_Owner = nullptr;
  BaseNodeClass *_Inner = nullptr;
  BaseNodeClass *_Prev = nullptr;
  BaseNodeClass *_Next = nullptr;

 public:
  bool autoinner = false;
  bool exit = false;
  bool _refersh = true;  // false => перерисовать только изменяемые поля
  byte type = 0;         // индекс периода / вида (зависит от узла)
  byte type1 = 0;        // индекс схемы

  virtual ~BaseNodeClass() {}

  virtual bool allowInner() { return true; }
  virtual bool allowOwner() { return true; }
  virtual bool allowNext() { return true; }
  virtual bool allowPrev() { return true; }

  virtual BaseNodeClass *getPrev() { return _Prev; }
  virtual BaseNodeClass *getNext() { return _Next; }
  virtual BaseNodeClass *getOwner() { return _Owner; }
  virtual BaseNodeClass *getInner() { return _Inner; }

  void setPrev(BaseNodeClass *node) { _Prev = node; }
  void setNext(BaseNodeClass *node) { _Next = node; }
  void setOwner(BaseNodeClass *node) { _Owner = node; }
  void setInner(BaseNodeClass *node) { _Inner = node; }

  // Связать два узла в кольцевом списке одного уровня.
  static void link(BaseNodeClass *first, BaseNodeClass *second) {
    first->setNext(second);
    second->setPrev(first);
  }

  virtual void show() {}
  virtual void deleteMenu() {}
  virtual void refresh() {}

  // Перерисовать только изменяемые поля, не мигая всем экраном.
  void renew() {
    _refersh = false;
    show();
    _refersh = true;
  }
};

// ---------------------------------------------------------------------------
// Узел, который сам создаёт своё подменю.
//
// Раньше этот код был скопирован в NodeBuilder, NodeTableBuilder,
// MainNodeBuilder и Menuconfig — каждый со своей копией ошибок:
//   * поле `BaseNodeClass **_listMenu;` НЕ инициализировалось, а getInner()
//     проверял `if (_listMenu != nullptr)` — то есть читал мусор из SRAM
//     и мог вернуть случайный указатель;
//   * при удалении самого узла его подменю не освобождалось — утечка;
//   * после deleteMenu() поле _Inner оставалось «висячим» указателем
//     на уже освобождённую память.
//
// Здесь всё это решено один раз.
// ---------------------------------------------------------------------------
class MenuOwnerNodeClass : public BaseNodeClass {
 protected:
  BaseNodeClass **_listMenu = nullptr;
  const byte _menuSize;

  explicit MenuOwnerNodeClass(byte size) : _menuSize(size) {}

  // Наполняет _listMenu и возвращает первый узел подменю.
  virtual BaseNodeClass *buildMenu() = 0;

 public:
  ~MenuOwnerNodeClass() override { releaseMenu(); }

  BaseNodeClass *getInner() override;
  void deleteMenu() override { releaseMenu(); }

 private:
  // Невиртуальный — безопасно вызывать из деструктора.
  void releaseMenu();
};

#endif
