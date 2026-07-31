//
//
//

#include "ControlSession.h"

#include <TimeLib.h>

#include "Alerting.h"
#include "StatusInfo.h"
#include "VentilationControl.h"
#include "objects.h"
#include "timing.h"
#include "io.h"

ControlSessionClass ControlSession;

constexpr int MINUTES_PER_DAY = 1440;

TimeShift ControlSessionClass::calculate(uint8_t countPerDay) {
  TimeShift ts;
  if (countPerDay == 0) return ts;  // skip == true
  ts.count = MINUTES_PER_DAY / countPerDay;
  if (ts.count == 0) ts.count = 1;
  ts.startIt = ts.count / 2;
  ts.skip = false;
  return ts;
}

bool ControlSessionClass::due(const TimeShift &data) {
  if (data.skip || data.count <= 0) return false;

  const int minutesToday = hour() * 60 + minute() + data.startIt;
  return (minutesToday % data.count == 0) && (minutesToday <= MINUTES_PER_DAY) && (second() < 30);
}

void ControlSessionClass::stopTray() { trayStop(); }

void ControlSessionClass::init() {
  center.update();
  if (center.read() == LOW) {
    StatusInfo.AddStatus(so_cent, 0);
    stopTray();
    _cetration = true;
    _needcenter = false;
  }

  _rotation = calculate(currentRow.GetRotate());
  if (_rotation.skip && !_cetration) _needcenter = true;

  _delayvent = calculate(currentRow.GetVentCount());

  _timing = millis();
  _starting = true;
}

void ControlSessionClass::startRotation() {
  StatusInfo.AddStatus(so_rot, 155);
  _timerot = millis();
  _rotchange = !_rotchange;
  _cetration = false;

  // Направление чередуется от поворота к повороту.
  if (_rotchange) {
    trayMoveRight();
  } else {
    trayMoveLeft();
  }

  _rotate = true;
}

void ControlSessionClass::refresh() {
  // ИСПРАВЛЕНО: было `if (millis() + _refreshtimmer > REFRESHDATA)` —
  // ПЛЮС вместо минуса. Условие выполнялось всегда, и уставка
  // пересчитывалась на каждой итерации loop() вместо раза в секунду.
  if (expired(_refreshtimmer, REFRESHDATA)) {
    _refreshtimmer = millis();
    currentSetTemp = currentRow.TempCelsius();
  }

  // --- дверь ---------------------------------------------------------------
  if (door.update() || _starting) {
    _starting = false;
    Alerting.SetWaitAllert();

    if (door.read() == HIGH) {  // дверь открыта
      _timing = millis();
      Hum = false;
      Heet = false;
      VentilationControl.wait();
      StatusInfo.AddStatus(so_door, 155);
      StatusInfo.AddStatus(so_cent, 155);
      if (!_cetration) _needcenter = true;
    } else {
      Hum = true;
      Heet = true;
      StatusInfo.AddStatus(so_door, 0);
      StatusInfo.AddStatus(so_cent, 0);
      Alerting.Finish(at_connect);
      _needcenter = false;
    }
  }

  // --- концевик центра лотка ----------------------------------------------
  if (center.update() && center.read() == LOW) {
    if (_needcenter) {
      stopTray();
      _cetration = true;
      _needcenter = false;
    }
    StatusInfo.AddStatus(so_cent, 0);
  }

  // --- поворот лотка -------------------------------------------------------
  if (_rotate) {
    if (expired(_timerot, ROTATEVENT)) {
      _timerot = 0;
      _rotate = false;
      StatusInfo.AddStatus(so_rot, 0);
      stopTray();
    }
  } else if ((due(_rotation) && door.read() == LOW) || _needcenter) {
    startRotation();
  }

  // --- при открытой двери дальше не работаем -------------------------------
  if (door.read() == HIGH) {
    if (expired(_timing, WAITOPENDOOR)) {
      _timing = millis();
      Alerting.Start(at_connect);
    }
    if (Hum || Heet) _starting = true;
    return;
  }

  // --- проветривание -------------------------------------------------------
  if (_ventelate) {
    const unsigned long ventDuration =
        static_cast<unsigned long>(currentRow.GetVentTime()) * 60UL * 1000UL;
    if (expired(_timevent, ventDuration)) {
      _timevent = 0;
      _ventelate = false;
      Hum = true;
      StatusInfo.AddStatus(so_blow, 0);
      VentilationControl.SetSpeed(0, fu_vent);
    }
  } else if (due(_delayvent)) {
    StatusInfo.AddStatus(so_blow, VENTDEFROTATE);
    VentilationControl.SetSpeed(VENTDEFROTATE, fu_vent);
    _timevent = millis();
    _ventelate = true;
    Hum = false;
  }
}
