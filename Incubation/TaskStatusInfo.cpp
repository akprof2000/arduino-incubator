//
//
//

#include "TaskStatusInfo.h"

#include <TimeLib.h>

#include "function.h"
#include "objects.h"

// Печать двузначного числа с ведущим нулём.
static void print2(uint8_t value) {
  if (value < 10) lcd.print('0');
  lcd.print(value);
}

void TaskStatusInfoClass::show() {
  lcd.setCursor(0, 0);
  lcd.print(T(Txt::Scheme));
  lcd.setCursor(8, 0);
  lcd.print(T(Txt::BirdFirst + currentTable));

  lcd.setCursor(0, 1);
  lcd.print(T(Txt::PDH));
  lcd.setCursor(3, 1);
  lcd.print(currentPeriod + 1);
  lcd.setCursor(8, 1);
  print2(currentDay);
  lcd.setCursor(14, 1);
  print2(currentHour);

  Serial.print(T(Txt::LogScheme));
  Serial.print(T(Txt::BirdFirst + currentTable));
  Serial.print(T(Txt::LogPeriod));
  Serial.print(currentPeriod + 1);
  Serial.print(T(Txt::LogDay));
  Serial.print(day());
  Serial.print(T(Txt::LogTime));
  Serial.print(hour());
  Serial.print(':');
  Serial.print(minute());
  Serial.print(':');
  Serial.println(second());
}
