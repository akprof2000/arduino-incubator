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
      
#define RESETLEDPIN 35
#define ALARMLEDPIN 35
#define ALARMSOUNDPIN 33


#define DOOREPIN A10

#define TRAYLEFTPIN 39
#define TRAYRIGHTPIN 37
constexpr auto TRAYCENTERPIN = 5;

#define HEATCONTROL 2

#define PEEKVALUE 5000
#define PEEKDEV 100

#define FANPIN 41
#define COOLERPIN 43

#define NEEDCHANGEPIN true
#define ROTATEVENT 90000
#define INTERVAL 9
#define PUSHINTERVAL 1000
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
