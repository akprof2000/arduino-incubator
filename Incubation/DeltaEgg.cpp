//
//
//

#include "DeltaEgg.h"

#include "function.h"
#include "objects.h"
#include "storage.h"

void DeltaEggClass::show() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(T(Txt::EggDeltaMin));
  lcd.setCursor(0, 1);
  lcd.print(T(Txt::EggDeltaMax));
  drawFields();
}

void DeltaEggClass::drawFields() {
  lcd.setCursor(12, 0);
  if (hidden(1)) {
    lcd.print(T(Txt::Blank4));
  } else {
    lcd.print(deltaEggMin / 10.0, 1);
    padTo(12 + (deltaEggMin > 99 ? 4 : 3), 16);
  }

  lcd.setCursor(12, 1);
  if (hidden(2)) {
    lcd.print(T(Txt::Blank4));
  } else {
    lcd.print(deltaEggMax / 10.0, 1);
    padTo(12 + (deltaEggMax > 99 ? 4 : 3), 16);
  }
}

void DeltaEggClass::editField(byte field) {
  float val = (field == 1) ? deltaEggMin : deltaEggMax;
  if (!scrollBar(0, 100, 1, val)) return;

  if (field == 1) {
    deltaEggMin = static_cast<byte>(val);
    // Нижний порог не может оказаться выше верхнего — иначе управление
    // охлаждением «залипало» бы во включённом состоянии.
    if (deltaEggMin > deltaEggMax) deltaEggMax = deltaEggMin;
  } else {
    deltaEggMax = static_cast<byte>(val);
    if (deltaEggMax < deltaEggMin) deltaEggMin = deltaEggMax;
  }
}

void DeltaEggClass::commit() {
  saveSetting(Eeprom::DeltaEggMin, deltaEggMin);
  saveSetting(Eeprom::DeltaEggMax, deltaEggMax);
}
