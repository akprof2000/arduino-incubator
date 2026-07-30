//
//
//

#include "RowRotateVent.h"

#include "DataRow.h"
#include "function.h"
#include "objects.h"

byte RowRotateVentClass::nextField(byte current) const {
  byte next = current + 1;
  if (next == 3 && _vent == 0) next++;
  return next;
}

void RowRotateVentClass::show() {
  DataRowClass row;
  row.init(type, type1);
  _rotate = row.GetRotate();
  _vent = row.GetVentCount();
  _venttime = row.GetVentTime();

  lcd.clear();
  drawFields();
}

// БЫЛО: два метода с флагом `_write`, который пытался вспомнить,
// перерисовывалась ли уже подпись строки. Логика ломалась при переходе
// значения через ноль и оставляла на экране обрывки старой подписи.
// Теперь строка перерисовывается целиком — это и проще, и всегда верно.
void RowRotateVentClass::drawFields() {
  // --- строка 0: поворот ---
  lcd.setCursor(0, 0);
  lcd.print(T(_rotate == 0 ? Txt::RotateOff : Txt::RotateOn));
  if (_rotate != 0) {
    lcd.setCursor(8, 0);
    if (hidden(1)) {
      lcd.print(T(Txt::Blank2));
    } else {
      lcd.print(_rotate);
      padTo(8 + (_rotate > 9 ? 2 : 1), 10);
    }
  } else if (hidden(1)) {
    lcd.setCursor(8, 0);
    lcd.print(T(Txt::Blank4));
  }

  // --- строка 1: проветривание ---
  lcd.setCursor(0, 1);
  lcd.print(T(_vent == 0 ? Txt::VentOff : Txt::VentOn));
  if (_vent == 0) {
    if (hidden(2)) {
      lcd.setCursor(4, 1);
      lcd.print(T(Txt::Blank3));
    }
    return;
  }

  lcd.setCursor(4, 1);
  if (hidden(2)) {
    lcd.print(T(Txt::Blank2));
  } else {
    lcd.print(_vent);
    padTo(4 + (_vent > 9 ? 2 : 1), 6);
  }

  lcd.setCursor(13, 1);
  if (hidden(3)) {
    lcd.print(T(Txt::Blank2));
  } else {
    lcd.print(_venttime);
    padTo(13 + (_venttime > 9 ? 2 : 1), 15);
  }
}

void RowRotateVentClass::editField(byte field) {
  if (field == 1) {
    float val = _rotate;
    if (!scrollBar(0, 50, 1, val)) return;
    _rotate = static_cast<byte>(val);
  } else if (field == 2) {
    float val = _vent;
    if (!scrollBar(0, 90, 1, val)) return;
    _vent = static_cast<byte>(val);
    // Включили проветривание — длительность должна быть осмысленной.
    if (_vent != 0 && _venttime < 3) _venttime = 3;
  } else {
    float val = _venttime;
    if (!scrollBar(3, 30, 1, val)) return;
    _venttime = static_cast<byte>(val);
  }
}

void RowRotateVentClass::commit() {
  DataRowClass row;
  row.init(type, type1);
  row.SetRotate(_rotate);
  row.SetVentCount(_vent);
  row.SetVentTime(_venttime);
  row.save();
}
