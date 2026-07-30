// objects.h
//
// Глобальные объекты и состояние прибора.

#pragma once
#ifndef _OBJECTS_h
#define _OBJECTS_h

#include <Arduino.h>
#include <Bounce2.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#include "DataRow.h"
#include "LCDAdjustments.h"
#include "LiquidCrystalRus.h"
#include "SparkFunHTU21D.h"
#include "consts.h"
#include "types.h"

// ---------------------------------------------------------------------------
// ВНИМАНИЕ (исправленная ошибка).
//
// Раньше здесь лежали объекты
//     const Bounce pinbounced0 = Bounce(BUTTON_L, INTERVAL);  // ... и ещё три
// Переменные с `const` на уровне пространства имён имеют ВНУТРЕННЮЮ связь,
// поэтому в КАЖДОМ .cpp, подключавшем objects.h (а это почти весь проект),
// создавалась своя копия всех четырёх Bounce. Десятки лишних объектов
// в SRAM плюс лишние вызовы pinMode() на старте.
//
// Теперь bouncer[] — единственный экземпляр, определённый в objects.cpp.
// ---------------------------------------------------------------------------
extern Bounce bouncer[BUTTON_COUNT];

extern LiquidCrystalRus lcd;
extern LCDAdjustments adjustments;

extern DataRowClass currentRow;
extern OneWire oneWire;
extern DallasTemperature sensors;
extern HTU21D myHumidity;

// --- состояние кнопок ------------------------------------------------------
extern ButtonState bState[BUTTON_COUNT];
extern bool appl[BUTTON_COUNT];             // «нажатие уже обработано»
extern unsigned long bPressTime[BUTTON_COUNT];
extern bool toroot;                         // запрос возврата в корень меню

// --- настройки (зеркало EEPROM) --------------------------------------------
extern byte bright;       // яркость подсветки, %
extern byte contr;        // контраст, %
extern byte minheat;      // минимальный процент нагрева
extern byte minhum;       // минимальный процент увлажнения
extern byte deltaEggMin;  // перегрев яйца: нижний порог, 0.1 °C
extern byte deltaEggMax;  // перегрев яйца: верхний порог, 0.1 °C
extern byte alTmpDel;     // порог включения нагрева, 0.1 °C
extern byte alTmpMax;     // аварийное отклонение по температуре, °C
extern byte alHumDel;     // порог включения увлажнения, %
extern byte alHumMax;     // аварийное отклонение по влажности, %

// --- состояние цикла инкубации ---------------------------------------------
extern byte currentDay;
extern byte currentHour;
extern byte currentPeriod;
extern byte currentTable;
extern byte started;
extern byte timerUpdated;

// --- измерения --------------------------------------------------------------
extern float currentTemp;       // температура основного датчика (HTU21D)
extern float currentFirstTemp;  // температура яйца (DS18B20 #1)
extern float currentHumd;       // относительная влажность, %
extern float currentSetTemp;    // уставка температуры по текущему режиму

// Показание влажности >= HUM_INVALID означает отказ датчика.
bool humidityValid(float value);

#endif
