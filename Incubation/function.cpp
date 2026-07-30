//
// Общие помощники отрисовки и ввода.
//

#include "function.h"

#include "objects.h"
#include "timing.h"

BaseNodeClass **createListMenu(byte size) {
  BaseNodeClass **listMenu = new BaseNodeClass *[size];
  if (listMenu == nullptr) return nullptr;  // куча кончилась — не падаем
  for (byte i = 0; i < size; i++) {
    listMenu[i] = nullptr;
  }
  return listMenu;
}

void deleteListMenu(byte size, BaseNodeClass **listMenu) {
  if (listMenu == nullptr) return;
  for (byte i = 0; i < size; i++) {
    delete listMenu[i];
    listMenu[i] = nullptr;
  }
  delete[] listMenu;
}

// ---------------------------------------------------------------------------
// Прокрутка значения кнопками
// ---------------------------------------------------------------------------
static unsigned long _scrollTime = 0;

bool scrollBar(float minval, float maxval, float curstep, float &val) {
  if (!expired(_scrollTime, REFRESHS_SROLL)) return false;
  _scrollTime = millis();

  // btn_down — одиночное нажатие (шаг и «залипание» через appl),
  // btn_push — удержание (автоповтор без залипания).
  const bool upSingle = (bState[1] == btn_down && !appl[1]);
  const bool downSingle = (bState[2] == btn_down && !appl[2]);
  const bool upRepeat = (bState[1] == btn_push && !appl[1]);
  const bool downRepeat = (bState[2] == btn_push && !appl[2]);

  if (upSingle || upRepeat) {
    val += curstep;
    if (val > maxval) val = maxval;
    if (upSingle) appl[1] = true;
    return true;
  }

  if (downSingle || downRepeat) {
    val -= curstep;
    if (val < minval) val = minval;
    if (downSingle) appl[2] = true;
    return true;
  }

  // ИСПРАВЛЕНО: в исходной версии здесь не было return — функция
  // завершалась без возвращаемого значения (undefined behaviour),
  // и вызывающий код получал случайный «мусор» вместо false.
  return false;
}

// ---------------------------------------------------------------------------
// Отрисовка
// ---------------------------------------------------------------------------
void padTo(uint8_t from, uint8_t to) {
  for (uint8_t i = from; i < to && i < LCDCOLS; i++) lcd.write(' ');
}

static void printCenteredP(uint8_t row, uint8_t id) {
  const uint8_t len = TLen(id);
  if (len == 0) return;
  const uint8_t left = (len >= LCDCOLS) ? 0 : (LCDCOLS - len) >> 1;
  lcd.setCursor(left, row);
  lcd.print(T(id));
}

void printCentered(uint8_t row, const char *text) {
  const uint8_t len = strLenLcd(text);
  if (len == 0) return;
  const uint8_t left = (len >= LCDCOLS) ? 0 : (LCDCOLS - len) >> 1;
  lcd.setCursor(left, row);
  lcd.print(text);
}

void showTwoLines(uint8_t id1, uint8_t id2) {
  lcd.clear();
  printCenteredP(0, id1);
  printCenteredP(1, id2);
}

void showOneLine(uint8_t id) {
  lcd.clear();
  printCenteredP(0, id);
}
