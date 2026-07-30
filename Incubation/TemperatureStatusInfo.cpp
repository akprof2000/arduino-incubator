//
//
//

#include "TemperatureStatusInfo.h"

#include "function.h"
#include "objects.h"

TemperatureStatusInfoClass::TemperatureStatusInfoClass() {
  sensors.setWaitForConversion(true);

  uint8_t found = sensors.getDeviceCount();
  if (found > MAX_TEMP_SENSORS) found = MAX_TEMP_SENSORS;

  for (uint8_t i = 0; i < found; i++) {
    if (!sensors.getAddress(_addr[i], i)) break;
    sensors.setResolution(_addr[i], TEMPERATURE_PRECISION);
    _count = i + 1;
  }

  sensors.setWaitForConversion(false);
}

void TemperatureStatusInfoClass::printSensor(uint8_t index) {
  if (index >= _count) {
    lcd.print(T(Txt::Dashes));
    Serial.print(T(Txt::Dashes));
    return;
  }

  const float tempC = sensors.getTempC(_addr[index]);
  if (tempC <= DEVICE_DISCONNECTED_C) {
    lcd.print(T(Txt::Dashes));
    Serial.print(T(Txt::Dashes));
    return;
  }

  if (tempC > _max) _max = tempC;
  if (tempC < _min) _min = tempC;

  lcd.print(tempC, 1);
  Serial.print(tempC, 1);
}

void TemperatureStatusInfoClass::show() {
  sensors.requestTemperatures();

  if (_refersh) {
    lcd.setCursor(0, 0);
    lcd.print(T(Txt::Temps12));
    lcd.setCursor(0, 1);
    lcd.print(T(Txt::Temps34));
  }

  _max = -127;
  _min = 127;

  Serial.print(T(Txt::LogTemp));

  // Четыре позиции на экране: (3,0) (11,0) (3,1) (11,1)
  static const uint8_t COL[MAX_TEMP_SENSORS] = {3, 11, 3, 11};
  static const uint8_t ROW[MAX_TEMP_SENSORS] = {0, 0, 1, 1};

  for (uint8_t i = 0; i < MAX_TEMP_SENSORS; i++) {
    Serial.print(T(Txt::LogSensor1 + i));
    lcd.setCursor(COL[i], ROW[i]);
    printSensor(i);
  }

  Serial.println();

  if (currentTemp > _max) _max = currentTemp;
  if (currentTemp < _min) _min = currentTemp;
}
