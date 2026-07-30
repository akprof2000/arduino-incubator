//
//
//

#include "HeatingControl.h"

#include "ControlSession.h"
#include "StatusInfo.h"
#include "VentilationControl.h"
#include "consts.h"
#include "objects.h"

HeatingControlClass HeatingControl;

// Мощность по квадратичному закону: 0 -> 0 %, deviationMax -> 100 %.
// Ограничена снизу значением minPercent (иначе исполнительное устройство
// «жужжит», не создавая полезного эффекта).
static double quadraticPower(double deviation, uint8_t deviationMax, uint8_t minPercent) {
  // ИСПРАВЛЕНО: раньше здесь было 0xFF / sq(alTmpMax) без проверки —
  // при alTmpMax == 0 (а его можно было выставить в меню) получалось
  // деление на ноль и NaN на выходе регулятора.
  if (deviationMax == 0) return 0;

  const double scale = 255.0 / (static_cast<double>(deviationMax) * deviationMax);
  double power = deviation * deviation * scale;

  const double floorPower = minPercent * 2.55;
  if (power < floorPower) power = floorPower;
  if (power > 255.0) power = 255.0;
  return power;
}

void HeatingControlClass::wait() {
  StatusInfo.AddStatus(so_cool, 0);
  StatusInfo.AddStatus(so_heet, 0);
  VentilationControl.SetSpeed(0, fu_temp);
  analogWrite(HEATCONTROL, 0);
}

// Обдув: снимает перегрев воздуха и, отдельно, перегрев самого яйца.
void HeatingControlClass::coolControl() {
  const double target = currentSetTemp;
  const double airExcess = currentTemp - target;
  const double eggExcess = currentFirstTemp - target;

  // Гистерезис по перегреву яйца: включаемся на deltaEggMax,
  // выключаемся только когда опустились ниже deltaEggMin.
  if (overHeating && eggExcess < deltaEggMin / 10.0) overHeating = false;

  if (eggExcess > deltaEggMax / 10.0 || overHeating) {
    overHeating = true;
    StatusInfo.AddStatus(so_cool, 0xFF);
    VentilationControl.SetSpeed(0xFF, fu_temp);
    return;
  }

  if (airExcess <= 0) {
    VentilationControl.SetSpeed(0, fu_temp);
    StatusInfo.AddStatus(so_cool, 0);
    return;
  }

  if (airExcess >= alTmpMax) {
    StatusInfo.AddStatus(so_cool, 0xFF);
    VentilationControl.SetSpeed(0xFF, fu_temp);
    return;
  }

  if (airExcess > alTmpDel / 10.0) {
    const double power = quadraticPower(airExcess, alTmpMax, minheat);
    StatusInfo.AddStatus(so_cool, power);
    VentilationControl.SetSpeed(power, fu_temp);
  }
  // Иначе — зона нечувствительности, мощность обдува не трогаем.
}

void HeatingControlClass::refresh() {
  const float target = currentSetTemp;
  const float deficit = target - currentTemp;

  coolControl();

  // Греть нельзя, если яйцо уже теплее уставки на deltaEggMin.
  if (deficit <= 0 || (currentFirstTemp - target > deltaEggMin / 10.0)) {
    StatusInfo.AddStatus(so_heet, 0);
    analogWrite(HEATCONTROL, 0);
    return;
  }

  if (deficit >= alTmpMax) {
    StatusInfo.AddStatus(so_heet, 0xFF);
    analogWrite(HEATCONTROL, 0xFF);
    return;
  }

  if (deficit > alTmpDel / 10.0) {
    const double power = quadraticPower(deficit, alTmpMax, minheat);
    analogWrite(HEATCONTROL, static_cast<int>(power));
    StatusInfo.AddStatus(so_heet, power);
  }
}
