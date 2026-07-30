// TemperatureStatusInfo.h

#ifndef _TEMPERATURESTATUSINFO_h
#define _TEMPERATURESTATUSINFO_h

#include <Arduino.h>
#include <DallasTemperature.h>

#include "BaseNode.h"
#include "consts.h"

// Экран показаний до четырёх датчиков DS18B20.
class TemperatureStatusInfoClass : public BaseNodeClass {
 public:
  TemperatureStatusInfoClass();
  void show() override;

 private:
  // БЫЛО: массив адресов выделялся в куче (`new address*[n]`, потом
  // `new address()` на каждый датчик), а деструктор освобождал его
  // через `delete lDev` вместо `delete[] lDev` — неопределённое поведение
  // и утечка. Размер к тому же перечитывался из getDeviceCount(),
  // который мог вернуть другое число, чем при выделении.
  //
  // Датчиков физически не больше четырёх (столько помещается на экран),
  // поэтому массив статический — куча не задействована вовсе.
  DeviceAddress _addr[MAX_TEMP_SENSORS];
  uint8_t _count = 0;
  float _max = 0;
  float _min = 0;

  void printSensor(uint8_t index);
};

#endif
