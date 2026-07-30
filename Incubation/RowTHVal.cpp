//
//
//

#include "RowTHVal.h"

#include "DataRow.h"
#include "consts.h"
#include "function.h"
#include "objects.h"

void RowTHValClass::show() {
  DataRowClass row;
  row.init(type, type1);
  _temp = row.GetTemp();
  _hum = row.GetHum();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(T(Txt::Temperature));
  lcd.setCursor(0, 1);
  lcd.print(T(Txt::Humidity));
  drawFields();
}

void RowTHValClass::drawFields() {
  lcd.setCursor(12, 0);
  if (hidden(1)) {
    lcd.print(T(Txt::Blank4));
  } else {
    lcd.print(BASETEMP + _temp / 10.0, 1);
  }

  lcd.setCursor(11, 1);
  if (hidden(2)) {
    lcd.print(T(Txt::Blank2));
  } else {
    lcd.print(BASEHUM + _hum);
  }
}

void RowTHValClass::editField(byte field) {
  if (field == 1) {
    float val = _temp;
    if (!scrollBar(0, 200, 1, val)) return;
    _temp = static_cast<byte>(val);
  } else {
    float val = _hum;
    if (!scrollBar(0, 40, 1, val)) return;
    _hum = static_cast<byte>(val);
  }
  drawFields();
}

void RowTHValClass::commit() {
  DataRowClass row;
  row.init(type, type1);
  row.SetTemp(_temp);
  row.SetHum(_hum);
  row.save();
}
