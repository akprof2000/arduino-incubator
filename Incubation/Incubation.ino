/*
  Инкубатор на ATmega2560.

  Автор: Aleksey Kozlov, 2017
  Лицензия: MIT

  Точка входа. Вся содержательная логика разнесена по классам:
    NodeManager       — экраны и кнопки
    ControlSession    — суточное расписание (поворот лотка, проветривание)
    HeatingControl    — контур температуры
    HumidityControl   — контур влажности
    VentilationControl— общий вентилятор
    Alerting          — аварийная сигнализация
*/

#include <DS1307RTC.h>
#include <EEPROM.h>
#include <GyverWDT.h>
#include <TimeLib.h>

#include "Alerting.h"
#include "ControlSession.h"
#include "HeatingControl.h"
#include "HumidityControl.h"
#include "NodeManager.h"
#include "StatusInfo.h"
#include "VentilationControl.h"
#include "objects.h"
#include "storage.h"
#include "timing.h"
#include "io.h"

static unsigned long sensorTimer = 0;
static uint8_t deviceCount = 0;

// ---------------------------------------------------------------------------
// Инициализация
// ---------------------------------------------------------------------------
static void setupPins() {
  pinMode(BUTTON_U, INPUT_PULLUP);
  pinMode(BUTTON_R, INPUT_PULLUP);
  pinMode(BUTTON_L, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);
  pinMode(DOOREPIN, INPUT_PULLUP);
  pinMode(TRAYCENTERPIN, INPUT_PULLUP);

  // Все нагрузки — в безопасное состояние, с учётом полярности
  // и без кратковременного включения в момент настройки вывода.
  actuatorsInitSafe();
}

// Полный сброс: удерживать кнопку «вниз» при подаче питания.
// БЫЛО: ~130 строк копипасты `currentRow.writeRow(...); currentRow.save();`
// прямо здесь. Теперь заводские таблицы лежат во FLASH (см. storage.cpp).
static void handleFactoryReset() {
  if (digitalRead(BUTTON_D) != LOW) return;

  const unsigned long pressStart = millis();

  while (digitalRead(BUTTON_D) == LOW) {
    // Мигаем, пока кнопка удерживается; после RESETINTERVAL — горим ровно.
    const bool confirmed = elapsed(pressStart) > RESETINTERVAL;
    alarmLedSet(true);
    delay(50);
    if (!confirmed) alarmLedSet(false);
    delay(50);
  }

  if (elapsed(pressStart) <= RESETINTERVAL) return;

  for (uint16_t i = 0; i < EEPROM.length(); i++) EEPROM.update(i, 0);
  writeFactoryTables();

  for (uint8_t i = 0; i < 3; i++) {
    alarmLedSet(true);
    delay(500);
    alarmLedSet(false);
    delay(500);
  }
}

// Значения по умолчанию заданы при объявлении в objects.cpp;
// здесь они либо перечитываются из EEPROM, либо туда записываются.
static void loadSettings() {
  if (EEPROM.read(Eeprom::Magic) != 0) {
    bright = EEPROM.read(Eeprom::Bright);
    contr = EEPROM.read(Eeprom::Contrast);
    alTmpDel = EEPROM.read(Eeprom::AlTmpDel);
    alTmpMax = EEPROM.read(Eeprom::AlTmpMax);
    alHumDel = EEPROM.read(Eeprom::AlHumDel);
    alHumMax = EEPROM.read(Eeprom::AlHumMax);
    currentDay = EEPROM.read(Eeprom::CurrentDay);
    currentPeriod = EEPROM.read(Eeprom::CurrentPeriod);
    currentTable = EEPROM.read(Eeprom::CurrentTable);
    started = EEPROM.read(Eeprom::Started);
    currentHour = EEPROM.read(Eeprom::CurrentHour);
    minheat = EEPROM.read(Eeprom::MinHeat);
    minhum = EEPROM.read(Eeprom::MinHum);
    deltaEggMin = EEPROM.read(Eeprom::DeltaEggMin);
    deltaEggMax = EEPROM.read(Eeprom::DeltaEggMax);
    timerUpdated = EEPROM.read(Eeprom::TimerUpdated);

    // Защита от «битой» EEPROM: с alTmpMax == 0 регулятор делил на ноль.
    if (alTmpMax == 0) alTmpMax = 2;
    if (alHumMax == 0) alHumMax = 15;
    if (currentPeriod >= Eeprom::Periods) currentPeriod = 0;
    if (currentTable >= Eeprom::Tables) currentTable = 0;
    return;
  }

  EEPROM.update(Eeprom::Bright, bright);
  EEPROM.update(Eeprom::Contrast, contr);
  EEPROM.update(Eeprom::AlTmpDel, alTmpDel);
  EEPROM.update(Eeprom::AlTmpMax, alTmpMax);
  EEPROM.update(Eeprom::AlHumDel, alHumDel);
  EEPROM.update(Eeprom::AlHumMax, alHumMax);
  EEPROM.update(Eeprom::CurrentDay, currentDay);
  EEPROM.update(Eeprom::CurrentPeriod, currentPeriod);
  EEPROM.update(Eeprom::CurrentTable, currentTable);
  EEPROM.update(Eeprom::Started, started);
  EEPROM.update(Eeprom::CurrentHour, currentHour);
  EEPROM.update(Eeprom::MinHeat, minheat);
  EEPROM.update(Eeprom::MinHum, minhum);
  EEPROM.update(Eeprom::DeltaEggMin, deltaEggMin);
  EEPROM.update(Eeprom::DeltaEggMax, deltaEggMax);
  EEPROM.update(Eeprom::TimerUpdated, timerUpdated);
  EEPROM.update(Eeprom::Magic, Eeprom::MagicValue);
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("Start incubation project full log"));

  setupPins();
  lcd.begin(LCDCOLS, LCDROWS);

  myHumidity.begin();
  setSyncProvider(RTC.get);
  sensors.begin();

  for (uint8_t i = 0; i < BUTTON_COUNT; i++) bState[i] = btn_up;

  handleFactoryReset();
  loadSettings();

  adjustments.setup(BRITHPIN, CONTRPIN, bright, 100 - contr);

  currentRow.init(currentPeriod, currentTable);
  NodeManager.init();
  ControlSession.init();

  lcd.clear();

  sensors.setWaitForConversion(true);
  deviceCount = sensors.getDeviceCount();
  if (deviceCount > MAX_TEMP_SENSORS) deviceCount = MAX_TEMP_SENSORS;
  sensors.setWaitForConversion(false);

  Watchdog.enable(RESET_MODE, WDT_PRESCALER_1024);
}

// ---------------------------------------------------------------------------
// Опрос датчиков и проверка аварийных отклонений
// ---------------------------------------------------------------------------
static void readSensors() {
  sensors.requestTemperatures();

  const float eggTemp = sensors.getTempCByIndex(0);
  currentTemp = myHumidity.readTemperature();

  // Если основной датчик воздуха показывает меньше датчика яйца, а сам
  // датчик яйца уже вышел за аварийный предел — доверяем более горячему.
  const float target = currentRow.TempCelsius();
  if (currentTemp < eggTemp && (target + alTmpMax) < eggTemp &&
      currentTemp > (target - alTmpMax)) {
    currentTemp = eggTemp;
  }

  currentFirstTemp = (eggTemp > 0 && eggTemp < 100) ? eggTemp : currentTemp;
  currentHumd = myHumidity.readHumidity();
}

static void checkAlerts() {
  if (started == 0) {
    Alerting.Finish(at_hum);
    Alerting.Finish(at_temp);
    return;
  }

  if (!humidityValid(currentHumd)) {
    Alerting.Start(at_err);
    return;
  }
  Alerting.Finish(at_err);

  if (abs(currentHumd - currentRow.HumidityPercent()) > alHumMax) {
    Alerting.Start(at_hum);
  } else {
    Alerting.Finish(at_hum);
  }

  // Разброс между всеми датчиками должен укладываться в alTmpMax.
  float minTemp = 127;
  float maxTemp = -127;
  for (uint8_t i = 0; i < deviceCount; i++) {
    const float t = sensors.getTempCByIndex(i);
    if (t <= DEVICE_DISCONNECTED_C) continue;
    if (t < minTemp) minTemp = t;
    if (t > maxTemp) maxTemp = t;
  }
  if (currentTemp > maxTemp) maxTemp = currentTemp;
  if (currentTemp < minTemp) minTemp = currentTemp;

  const float target = currentSetTemp;
  if (abs(minTemp - target) > alTmpMax || abs(maxTemp - target) > alTmpMax) {
    Alerting.Start(at_temp);
  } else {
    Alerting.Finish(at_temp);
  }
}

// ---------------------------------------------------------------------------
// Ход времени: смена часа, дня и периода
// ---------------------------------------------------------------------------
static void syncRtc() {
  if (RTC.chipPresent()) {
    timerUpdated = 1;
    RTC.set(now());
  } else {
    timerUpdated = 0;
  }
  // ИСПРАВЛЕНО: было EEPROM.update(17, timerUpdated) — адрес 17 занят
  // под currentHour, значения затирали друг друга.
  EEPROM.update(Eeprom::TimerUpdated, timerUpdated);
}

static void advanceSchedule() {
  if (hour() != currentHour) {
    currentHour = hour();
    EEPROM.update(Eeprom::CurrentHour, currentHour);
    if (timerUpdated == 0) syncRtc();
  }

  if (currentDay != day()) {
    currentDay = day();
    EEPROM.update(Eeprom::CurrentDay, currentDay);
    ControlSession.init();
  }

  // Период закончился — переходим к следующему.
  if (currentRow.GetDay() >= day()) return;

  if (currentPeriod >= Eeprom::Periods - 1) {
    Alerting.Start(at_endplan);
    return;
  }

  currentPeriod++;
  currentDay = 0;
  currentHour = 0;
  currentRow.init(currentPeriod, currentTable);
  ControlSession.init();

  EEPROM.update(Eeprom::CurrentDay, currentDay);
  EEPROM.update(Eeprom::CurrentPeriod, currentPeriod);
  EEPROM.update(Eeprom::CurrentTable, currentTable);
  EEPROM.update(Eeprom::Started, 1);
  EEPROM.update(Eeprom::CurrentHour, currentHour);

  setTime(0, 0, 0, currentDay + 1, 1, 2017);
  syncRtc();
}

// ---------------------------------------------------------------------------
// Основной цикл
// ---------------------------------------------------------------------------
void loop() {
  // БЫЛО: сброс сторожевого таймера вызывался внутри условия «раз в секунду».
  // Стоило одному из вложенных вызовов задержаться (например, delay(3000)
  // при запуске цикла) — и контроллер уходил в перезагрузку.
  Watchdog.reset();

  if (expired(sensorTimer, REFRESHDATA)) {
    sensorTimer = millis();
    readSensors();
    checkAlerts();
  }

  advanceSchedule();

  if (humidityValid(currentHumd)) {
    ControlSession.refresh();

    if (ControlSession.Hum || ControlSession.Heet) {
      VentilationControl.refresh();
    } else {
      VentilationControl.wait();
    }

    if (ControlSession.Heet) {
      HeatingControl.refresh();
    } else {
      HeatingControl.wait();
    }

    if (ControlSession.Hum) {
      HumidityControl.refresh();
    } else {
      HumidityControl.wait();
    }
  } else {
    // Датчик влажности отказал — всё выключаем, чтобы не «выпарить» кладку.
    VentilationControl.wait();
    HeatingControl.wait();
    HumidityControl.wait();
  }

  Alerting.refresh();
  NodeManager.work();
}
