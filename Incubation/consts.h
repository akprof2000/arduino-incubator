// consts.h

#ifndef _CONSTS_h
#define _CONSTS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define BUTTON_L A15
#define BUTTON_R A12
#define BUTTON_U A13
#define BUTTON_D A14

constexpr auto RESETLEDPIN = 5;
constexpr auto ALARMLEDPIN = 5;
constexpr auto ALARMSOUNDPIN = 6;


#define DOOREPIN A10

constexpr auto TRAYLEFTPIN = 17;
constexpr auto TRAYRIGHTPIN = 18;
constexpr auto TRAYCENTERPIN = A11;

constexpr auto HEATCONTROL = 2;

constexpr auto PEEKVALUE = 5000;
constexpr auto PEEKDEV = 100;

constexpr auto FANPIN = 3;
constexpr auto COOLERPIN = 4;

constexpr auto ROTATEVENT = 20000;
constexpr auto INTERVAL = 9;
constexpr auto PUSHINTERVAL = 1000;
constexpr auto PROGRESSINT = 300;
constexpr auto SCROLLDELAY = 50;
constexpr auto DISPLAYINTERVAL = 3000;
constexpr auto ENDINTERVAL = 1000 * 5 * 60;
constexpr auto MENUEXIT = 60000;
constexpr auto BLINKINTERVAL = 500;
constexpr auto RESETINTERVAL = 5000;
constexpr auto ERRORINTERVAL = 500;
constexpr auto REFRESHDATA = 1000;
constexpr auto VENTDEFROTATE = 127;
constexpr auto SCROLLSPEED = 250;

constexpr auto WAITAFTEREVENT = 180000;
constexpr auto WAITOPENDOOR = 180000;

constexpr auto BASETEMP = 30;
constexpr auto BASEHUM = 45;

constexpr auto LCDCOLS = 16;
constexpr auto LCDROWS = 2;

constexpr auto BRITHPIN = 7;
constexpr auto CONTRPIN = 6;

constexpr auto LCDRS = 13;
constexpr auto LCDE = 12;
constexpr auto LCDD4 = 11;
constexpr auto LCDD5 = 10 ;
constexpr auto LCDD6 = 9;
constexpr auto LCDD7 = 8;

constexpr auto COEFF = 11.29158979063621;


constexpr auto ONE_WIRE_BUS = 19;
constexpr auto TEMPERATURE_PRECISION = 11;

#endif