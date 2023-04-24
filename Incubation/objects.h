// objects.h
#pragma once

#ifndef _OBJECTS_h
#define _OBJECTS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include <LiquidCrystalRus.h>
#include <Bounce2.h>
#include "consts.h"
#include "types.h"
#include "LCDAdjustments.h"
#include "DataRow.h"
#include "SparkFunHTU21D.h"
#include <OneWire.h>
#include <DallasTemperature.h>


const	Bounce pinbounced0 = Bounce(BUTTON_L, INTERVAL);
const	Bounce pinbounced1 = Bounce(BUTTON_U, INTERVAL);
const   Bounce pinbounced2 = Bounce(BUTTON_R, INTERVAL);
const   Bounce pinbounced3 = Bounce(BUTTON_D, INTERVAL);
extern  Bounce bouncer[4];
extern  LiquidCrystalRus lcd;
extern  LCDAdjustments adjustments;

extern  DataRowClass currentRow;
extern  OneWire oneWire;
extern  DallasTemperature sensors;


extern bool toroot;
extern ButtonState bState[4];
extern bool appl[4];
extern unsigned long bPressTime[4];

extern byte minheat;
extern byte minhum;

extern byte deltaEggMin;
extern byte deltaEggMax;



extern byte bright;
extern byte contr;

extern byte currentDay;
extern byte currentHour;
extern byte currentPeriod;
extern byte currentTable;
extern byte started;
extern bool allertEnable;
extern byte timerUpdated;

extern byte alTmpDel;
extern byte alTmpMax;
extern byte alHumDel;
extern byte alHumMax;

extern HTU21D myHumidity;

extern float currentTemp;
extern float currentFirstTemp;
extern float currentHumd;
extern float currentSetTemp;

#endif




