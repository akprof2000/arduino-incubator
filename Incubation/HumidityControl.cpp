//
//
//

#include "HumidityControl.h"

#include "StatusInfo.h"
#include "VentilationControl.h"
#include "consts.h"
#include "objects.h"
#include "timing.h"
#include "io.h"

HumidityControlClass HumidityControl;

// Тот же квадратичный закон, что и в контуре температуры.
static double quadraticPower(double deviation, uint8_t deviationMax, uint8_t minPercent) {
  if (deviationMax == 0) return 0;  // защита от деления на ноль

  const double scale = 255.0 / (static_cast<double>(deviationMax) * deviationMax);
  double power = deviation * deviation * scale;

  const double floorPower = minPercent * 2.6;
  if (power < floorPower) power = floorPower;
  if (power > 255.0) power = 255.0;
  return power;
}

void HumidityControlClass::wait() {
  StatusInfo.AddStatus(so_dry, 0);
  StatusInfo.AddStatus(so_wet, 0);
  VentilationControl.SetSpeed(0, fu_hum);
  evaporatorSet(false);
  _on = false;
}

// Осушение: избыток влаги убирается вытяжкой.
void HumidityControlClass::dryControl() {
  const float target = currentRow.HumidityPercent();
  const float excess = currentHumd - target;

  if (excess <= 0) {
    VentilationControl.SetSpeed(0, fu_hum);
    StatusInfo.AddStatus(so_dry, 0);
    return;
  }

  if (excess >= alHumMax) {
    StatusInfo.AddStatus(so_dry, 0xFF);
    VentilationControl.SetSpeed(0xFF, fu_hum);
    return;
  }

  if (excess > alHumDel) {
    const double power = quadraticPower(excess, alHumMax, minhum);
    StatusInfo.AddStatus(so_dry, power);
    VentilationControl.SetSpeed(power, fu_hum);
  }
}

void HumidityControlClass::refresh() {
  if (!humidityValid(currentHumd)) {
    evaporatorSet(false);
    StatusInfo.AddStatus(so_wet, 0);
    _on = false;
    return;
  }

  dryControl();

  const float target = currentRow.HumidityPercent();
  const float deficit = target - currentHumd;

  if (deficit <= 0) {
    evaporatorSet(false);
    StatusInfo.AddStatus(so_wet, 0);
    _on = false;
    return;
  }

  if (deficit >= alHumMax) {
    evaporatorSet(true);
    StatusInfo.AddStatus(so_wet, 0xFF);
    _on = true;
    return;
  }

  if (deficit <= alHumDel) return;  // зона нечувствительности

  const double power = quadraticPower(deficit, alHumMax, minhum);
  _delta = (255.0 - power) * PEEKVALUE / PEEKDEV;

  if (power >= 255 || _delta < PEEKVALUE) {
    StatusInfo.AddStatus(so_wet, 0xFF);
    // ИСПРАВЛЕНО: здесь испаритель ВЫКЛЮЧАЛСЯ при максимальном запросе
    // на увлажнение вместо того, чтобы включиться.
    evaporatorSet(true);
    _on = true;
    return;
  }

  StatusInfo.AddStatus(so_wet, power);

  // «Медленный» ШИМ испарителя.
  if (_on) {
    if (expired(_timer, PEEKVALUE)) {
      _timer = millis();
      _on = false;
      evaporatorSet(false);
    }
  } else {
    if (expired(_timer, static_cast<unsigned long>(_delta))) {
      _timer = millis();
      _on = true;
      evaporatorSet(true);
    }
  }
}
