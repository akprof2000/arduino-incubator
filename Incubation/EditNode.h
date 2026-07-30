// EditNode.h
//
// Общий каркас экрана редактирования.
//
// Шесть экранов (яркость/контраст, пороги T и H, минимальные проценты,
// перегрев яйца, длительность периода, уставки, поворот/проветривание)
// содержали почти дословно одинаковый код:
//
//   * три метода allowInner/allowNext/allowPrev с телом
//     `if (_shift > 0 && _shift < N) return false; else return true;`
//   * одинаковый блок мигания редактируемого поля,
//   * одинаковый переход по полям кнопкой OK с сохранением в EEPROM.
//
// Всё это теперь в одном месте.

#ifndef _EDITNODE_h
#define _EDITNODE_h

#include <Arduino.h>

#include "BaseNode.h"

class EditNodeClass : public BaseNodeClass {
 public:
  // Пока редактируется поле, уход с экрана запрещён — иначе значение
  // потерялось бы несохранённым.
  bool editing() const { return _shift > 0 && _shift <= _fieldCount; }
  bool allowInner() override { return !editing(); }
  bool allowNext() override { return !editing(); }
  bool allowPrev() override { return !editing(); }

  void refresh() override;

 protected:
  explicit EditNodeClass(byte fieldCount) : _fieldCount(fieldCount) {}

  // Отрисовать значения всех полей (с учётом мигания активного).
  virtual void drawFields() = 0;
  // Обработать вращение значения для поля `field` (1..fieldCount).
  virtual void editField(byte field) = 0;
  // Сохранить значения. Вызывается при каждом переключении поля.
  virtual void commit() {}
  // Позволяет пропускать неактуальные поля (например, время проветривания,
  // когда проветривание выключено).
  virtual byte nextField(byte current) const { return current + 1; }

  // Значение поля скрыто (мигает) — вместо него выводится заглушка.
  bool hidden(byte field) const { return _blinc && _shift == field; }

  byte _shift = 0;  // 0 — просмотр, 1..N — редактируется поле N
  const byte _fieldCount;

 private:
  bool _blinc = false;
  unsigned long _timer = 0;
};

#endif
