//
//
//

#include "RowDayCount.h"

#include "DataRow.h"
#include "function.h"
#include "objects.h"

void RowDayCountClass::show() {
  // БЫЛО: `DataRowClass *row = new DataRowClass(); ... delete row;`
  // — выделение в куче на каждой отрисовке экрана. Объект на стеке.
  DataRowClass row;
  row.init(type, type1);
  _day = row.GetDay();
  _from = row.GetFrom();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(T(Txt::DayFromTo));
  lcd.setCursor(0, 1);
  lcd.print(T(Txt::Period));
  drawFields();
}

void RowDayCountClass::drawFields() {
  lcd.setCursor(7, 0);
  lcd.print(_from);
  padTo(7 + (_from > 9 ? 2 : 1), 9);

  lcd.setCursor(13, 0);
  if (_day == 0) {
    lcd.print(T(Txt::Blank4));
  } else {
    const byte last = _from + _day - 1;
    if (last < 10) lcd.print('0');
    lcd.print(last);
  }

  lcd.setCursor(8, 1);
  if (hidden(1)) {
    lcd.print(T(Txt::Blank4));
  } else {
    lcd.print(_day);
    padTo(8 + (_day > 9 ? 2 : 1), 12);
  }
}

void RowDayCountClass::editField(byte field) {
  (void)field;
  float val = _day;
  if (!scrollBar(0, 30, 1, val)) return;
  _day = static_cast<byte>(val);
}

void RowDayCountClass::commit() {
  DataRowClass row;
  row.init(type, type1);
  row.SetDay(_day);
  row.save();
}
