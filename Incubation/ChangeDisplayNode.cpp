//
//
//

#include "ChangeDisplayNode.h"

#include "function.h"
#include "objects.h"
#include "storage.h"

void ChangeDisplayNodeClass::show() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(T(Txt::Brightness));
  lcd.setCursor(0, 1);
  lcd.print(T(Txt::Contrast));
  drawFields();
}

void ChangeDisplayNodeClass::drawFields() {
  lcd.setCursor(9, 0);
  if (hidden(1)) {
    lcd.print(T(Txt::Blank3));
  } else {
    lcd.print(bright);
    padTo(9 + (bright > 99 ? 3 : bright > 9 ? 2 : 1), 12);
  }

  lcd.setCursor(10, 1);
  if (hidden(2)) {
    lcd.print(T(Txt::Blank3));
  } else {
    lcd.print(contr);
    padTo(10 + (contr > 99 ? 3 : contr > 9 ? 2 : 1), 13);
  }
}

void ChangeDisplayNodeClass::editField(byte field) {
  float val = (field == 1) ? bright : contr;
  if (!scrollBar(0, 100, 1, val)) return;

  if (field == 1) {
    bright = static_cast<byte>(val);
  } else {
    contr = static_cast<byte>(val);
  }
  adjustments.setup(BRITHPIN, CONTRPIN, bright, 100 - contr);
}

void ChangeDisplayNodeClass::commit() {
  saveSetting(Eeprom::Bright, bright);
  saveSetting(Eeprom::Contrast, contr);
}
