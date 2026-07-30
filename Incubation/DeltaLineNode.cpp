//
//
//

#include "DeltaLineNode.h"

#include "function.h"
#include "objects.h"
#include "storage.h"

void DeltaLineNodeClass::show() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(T(isTemperature() ? Txt::TempC : Txt::HumidityPct));
  lcd.setCursor(0, 1);
  lcd.print(T(isTemperature() ? Txt::DeltaMaxT : Txt::DeltaMaxH));
  drawFields();
}

void DeltaLineNodeClass::drawFields() {
  lcd.setCursor(4, 1);
  if (hidden(1)) {
    lcd.print(T(Txt::Blank4));
  } else if (isTemperature()) {
    lcd.print(alTmpDel / 10.0, 1);
  } else {
    lcd.print(alHumDel);
    padTo(4 + (alHumDel > 9 ? 2 : 1), 8);
  }

  lcd.setCursor(14, 1);
  if (hidden(2)) {
    lcd.print(T(Txt::Blank2));
  } else {
    const byte value = isTemperature() ? alTmpMax : alHumMax;
    lcd.print(value);
    padTo(14 + (value > 9 ? 2 : 1), 16);
  }
}

void DeltaLineNodeClass::editField(byte field) {
  if (field == 1) {
    float val = isTemperature() ? alTmpDel : alHumDel;
    if (!scrollBar(1, isTemperature() ? 99 : 30, 1, val)) return;
    if (isTemperature()) {
      alTmpDel = static_cast<byte>(val);
    } else {
      alHumDel = static_cast<byte>(val);
    }
    return;
  }

  // ИСПРАВЛЕНО: раньше это поле для влажности инициализировалось из
  // alTmpMax (`float val = alTmpMax;`) и только потом перезаписывалось —
  // при переполнении диапазона в alHumMax могло попасть значение
  // температурного порога.
  float val = isTemperature() ? alTmpMax : alHumMax;
  if (!scrollBar(1, isTemperature() ? 10 : 50, 1, val)) return;
  if (isTemperature()) {
    alTmpMax = static_cast<byte>(val);
  } else {
    alHumMax = static_cast<byte>(val);
  }
}

void DeltaLineNodeClass::commit() {
  if (isTemperature()) {
    saveSetting(Eeprom::AlTmpDel, alTmpDel);
    saveSetting(Eeprom::AlTmpMax, alTmpMax);
  } else {
    saveSetting(Eeprom::AlHumDel, alHumDel);
    saveSetting(Eeprom::AlHumMax, alHumMax);
  }
}
