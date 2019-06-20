// consts.h

#ifndef _CONSTS_h
#define _CONSTS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define BUTTON_OK A14
#define BUTTON_M A15
#define BUTTON_P A13
      
constexpr auto RESETLEDPIN = 35;
constexpr auto ALARMLEDPIN = 35;
constexpr auto ALARMSOUNDPIN = 33;


#define DOOREPIN A10

constexpr auto TRAYLEFTPIN = 39;
constexpr auto TRAYRIGHTPIN = 37;
constexpr auto TRAYCENTERPIN = 5;

constexpr auto HEATCONTROL = 2;

constexpr auto PEEKVALUE = 5000;
constexpr auto PEEKDEV = 100;

constexpr auto FANPIN = 41;
constexpr auto COOLERPIN = 43;

constexpr auto NEEDCHANGEPIN = true;
constexpr auto ROTATEVENT = 90000;
constexpr auto INTERVAL = 9;
constexpr auto PUSHINTERVAL = 1000;
#define PROGRESSINT 300
#define SCROLLDELAY 50
#define DISPLAYINTERVAL 10000
#define MENUEXIT 60000
#define BLINKINTERVAL 500
#define RESETINTERVAL 5000
#define ERRORINTERVAL 500
#define REFRESHDATA 1000
#define VENTDEFROTATE 127
#define SCROLLSPEED 250

#define WAITAFTEREVENT 180000
#define WAITOPENDOOR 180000

#define BASETEMP 30
#define BASEHUM 45

#define LCDCOLS 16
#define LCDROWS 2

#define BRITHPIN 45
#define CONTRPIN 6

#define LCDRS 13
#define LCDE 12
#define LCDD4 8
#define LCDD5 11 
#define LCDD6 9
#define LCDD7 10

#define COEFF 11.29158979063621


#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 11

#endif
