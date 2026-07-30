//
//
//

#include "MinActionPercent.h"

#include "function.h"
#include "objects.h"
#include "storage.h"

void MinActionPercentClass::show() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(T(Txt::MinHeat));
  lcd.setCursor(0, 1);
  lcd.print(T(Txt::MinHum));
  drawFields();
}

void MinActionPercentClass::drawFields() {
  lcd.setCursor(12, 0);
  if (hidden(1)) {
    lcd.print(T(Txt::Blank3));
  } else {
    lcd.print(minheat);
    padTo(12 + (minheat > 99 ? 3 : minheat > 9 ? 2 : 1), 15);
  }

  lcd.setCursor(9, 1);
  if (hidden(2)) {
    lcd.print(T(Txt::Blank3));
  } else {
    lcd.print(minhum);
    padTo(9 + (minhum > 99 ? 3 : minhum > 9 ? 2 : 1), 12);
  }
}

void MinActionPercentClass::editField(byte field) {
  float val = (field == 1) ? minheat : minhum;
  if (!scrollBar(0, 100, 1, val)) return;
  if (field == 1) {
    minheat = static_cast<byte>(val);
  } else {
    minhum = static_cast<byte>(val);
  }
}

void MinActionPercentClass::commit() {
  saveSetting(Eeprom::MinHeat, minheat);
  saveSetting(Eeprom::MinHum, minhum);
}
