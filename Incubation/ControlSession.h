// ControlSession.h

#ifndef _CONTROLSESSION_h
#define _CONTROLSESSION_h

#include <Arduino.h>
#include <Bounce2.h>

#include "consts.h"

// Расписание периодических событий внутри суток.
struct TimeShift {
  int count = 0;     // интервал между событиями, мин
  int startIt = 0;   // смещение первого события, мин
  bool skip = true;  // событие отключено
};

// Планировщик суточных операций: поворот лотка, проветривание,
// отслеживание двери и центрирования.
class ControlSessionClass {
 public:
  bool Hum = true;   // разрешено ли сейчас увлажнять
  bool Heet = true;  // разрешено ли сейчас греть

  void init();
  void refresh();

 private:
  static TimeShift calculate(uint8_t countPerDay);
  static bool due(const TimeShift &data);

  Bounce door = Bounce(DOOREPIN, INTERVAL);
  Bounce center = Bounce(TRAYCENTERPIN, INTERVAL);

  TimeShift _delayvent;
  TimeShift _rotation;

  bool _ventelate = false;
  bool _rotate = false;
  bool _rotchange = false;
  bool _needcenter = false;
  bool _cetration = false;
  bool _starting = false;

  unsigned long _refreshtimmer = 0;
  unsigned long _timerot = 0;
  unsigned long _timevent = 0;
  unsigned long _timing = 0;

  void stopTray();
  void startRotation();
};

extern ControlSessionClass ControlSession;

#endif
