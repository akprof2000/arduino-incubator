//
//
//

#include "ScrollTextNode.h"

#include "consts.h"
#include "function.h"
#include "objects.h"
#include "timing.h"

char ScrollTextNodeClass::_buffer[ScrollTextNodeClass::BUFFER_SIZE];
const void *ScrollTextNodeClass::_owner = nullptr;
uint8_t ScrollTextNodeClass::_cells = 0;

uint16_t ScrollTextNodeClass::hashOf(const char *s) {
  uint16_t h = 5381;
  while (*s) h = static_cast<uint16_t>(h * 33u) ^ static_cast<uint8_t>(*s++);
  return h;
}

void ScrollTextNodeClass::show() {
  // Экран мог смениться — тогда в буфере лежит чужой текст и перерисовать
  // надо в любом случае, даже если наш собственный текст не поменялся.
  const bool wasMine = (_owner == this);

  TextBuilder builder(_buffer, BUFFER_SIZE);
  buildText(builder);
  _owner = this;
  _cells = strLenLcd(_buffer);

  const uint16_t hash = hashOf(_buffer);
  const bool unchanged = wasMine && _hasHash && hash == _hash;

  lcd.setCursor(0, 0);
  lcd.print(T(_titleId));

  if (unchanged) return;  // содержимое не поменялось — не мигаем экраном

  _hash = hash;
  _hasHash = true;
  _start = 0;

  Serial.print(T(_titleId));
  Serial.print(T(Txt::LogColon));
  Serial.println(_buffer);

  if (_cells > LCDCOLS) {
    drawScroll();  // длинный текст поедет строкой
  } else {
    showTwoLines(_titleId, Txt::Empty);
    printCentered(1, _buffer);
  }
}

void ScrollTextNodeClass::refresh() {
  if (_owner != this) return;      // буфер уже занят другим экраном
  if (_cells <= LCDCOLS) return;   // прокручивать нечего
  if (!expired(_time, SCROLLSPEED)) return;
  _time = millis();
  drawScroll();
}

void ScrollTextNodeClass::drawScroll() {
  const uint8_t total = _cells + GAP;

  // Найти байт, с которого начинается знакоместо номер _start.
  const char *p = _buffer;
  for (uint8_t cell = 0; cell < _start && *p;) {
    p++;
    if ((static_cast<uint8_t>(*p) & 0xC0) != 0x80) cell++;
  }

  lcd.setCursor(0, 1);
  uint8_t cell = _start;
  for (uint8_t i = 0; i < LCDCOLS; i++) {
    if (cell < _cells && *p) {
      const uint8_t c = static_cast<uint8_t>(*p++);
      lcd.write(c);
      // Кириллица в UTF-8 — два байта; второй тоже надо отдать дисплею,
      // он сам склеит их в один символ.
      if ((c & 0xE0) == 0xC0 && *p) lcd.write(static_cast<uint8_t>(*p++));
    } else {
      lcd.write(' ');
    }

    cell++;
    if (cell >= total) {
      cell = 0;
      p = _buffer;
    }
  }

  _start++;
  if (_start >= total) _start = 0;
}
