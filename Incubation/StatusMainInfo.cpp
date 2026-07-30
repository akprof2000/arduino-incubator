//
//
//

#include "StatusMainInfo.h"

#include "Alerting.h"
#include "consts.h"
#include "function.h"
#include "objects.h"

void StatusMainInfoClass::show() {
  const float humd = myHumidity.readHumidity();
  currentHumd = humd;

  if (started == 0) {
    _work = false;
    Alerting.Start(at_endplan);
    showTwoLines(Txt::ChooseMode1, Txt::ChooseMode2);
    Serial.print(T(Txt::ChooseMode1));
    Serial.print(' ');
    Serial.println(T(Txt::ChooseMode2));
    return;
  }

  if (!humidityValid(humd)) {
    _work = false;
    showTwoLines(Txt::Alarm1, Txt::Alarm2);
    Serial.print(T(Txt::Alarm1));
    Serial.print(' ');
    Serial.println(T(Txt::Alarm2));
    return;
  }

  _work = true;

  if (_refersh) {
    lcd.setCursor(0, 0);
    lcd.print(T(Txt::StatusT));
    lcd.setCursor(0, 1);
    lcd.print(T(Txt::StatusH));
  }

  // БЫЛО: readTemperature() вызывался дважды подряд — лишний обмен по I2C
  // на каждой отрисовке.
  currentTemp = myHumidity.readTemperature();

  lcd.setCursor(5, 0);
  lcd.print(currentSetTemp, 1);
  lcd.setCursor(5, 1);
  lcd.print(currentRow.HumidityPercent());
  padTo(7, 9);

  lcd.setCursor(12, 0);
  lcd.print(currentTemp, 1);
  lcd.setCursor(12, 1);
  lcd.print(humd, 0);
  padTo(14, 16);

  Serial.print(T(Txt::LogTempSet));
  Serial.print(currentRow.TempCelsius(), 1);
  Serial.print(T(Txt::LogCurrent));
  Serial.println(currentTemp, 1);

  Serial.print(T(Txt::LogHumSet));
  Serial.print(currentRow.HumidityPercent());
  Serial.print(T(Txt::LogCurrent));
  Serial.println(humd, 1);
}
