// ScrollTextNode.h
//
// Экран «заголовок + бегущая строка».
//
// Заменяет две почти одинаковые копии кода в CurrentOperation и
// AlertInfoNode, в каждой из которых был один и тот же выход за границы
// массива:
//
//     char lcdTop[LCDCOLS << 1];              // 32 байта на стеке
//     memcpy(&lcdTop[0], &message[pos], 32);  // читает 32 байта ЛЮБОЙ строки
//     lcd.print(lcdTop);                      // печатает до первого '\0'
//
// Строка могла быть короче 32 байт (тогда memcpy читал чужую память),
// а завершающий '\0' в lcdTop не ставился вовсе — lcd.print() уходил
// в соседние байты стека и печатал мусор, пока случайно не встречал ноль.

#ifndef _SCROLLTEXTNODE_h
#define _SCROLLTEXTNODE_h

#include <Arduino.h>

#include "BaseNode.h"
#include "texts.h"

class ScrollTextNodeClass : public BaseNodeClass {
 public:
  void show() override;
  void refresh() override;

 protected:
  explicit ScrollTextNodeClass(uint8_t titleId) : _titleId(titleId) {}

  // Наполнить builder текущим содержимым строки.
  virtual void buildText(TextBuilder &builder) = 0;

 private:
  // Одновременно на экране только один такой узел, поэтому буфер общий.
  static constexpr uint8_t BUFFER_SIZE = 240;
  static constexpr uint8_t GAP = 4;  // пробелов между концом и началом
  static char _buffer[BUFFER_SIZE];
  static const void *_owner;  // какому узлу принадлежит содержимое буфера
  static uint8_t _cells;      // длина содержимого в знакоместах

  uint8_t _titleId;
  uint16_t _hash = 0;
  bool _hasHash = false;
  uint8_t _start = 0;
  unsigned long _time = 0;

  void drawScroll();
  static uint16_t hashOf(const char *s);
};

#endif
