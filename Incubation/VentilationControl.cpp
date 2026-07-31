//
//
//

#include "VentilationControl.h"

#include "objects.h"
#include "timing.h"
#include "io.h"

VentilationControlClass VentilationControl;

void VentilationControlClass::SetSpeed(double val, FanUser user) {
  long request = lround(val);
  if (request < 0) request = 0;
  if (request > 255) request = 255;
  const byte value = static_cast<byte>(request);

  switch (user) {
    case fu_hum:
      _curr_hum = value;
      break;
    case fu_temp:
      _curr_temp = value;
      break;
    case fu_vent:
      _curr_vent = value;
      break;
    default:
      break;
  }

  // Побеждает самый «требовательный» потребитель.
  byte result = _curr_hum;
  if (result < _curr_vent) result = _curr_vent;
  if (result < _curr_temp) result = _curr_temp;
  _currentVal = result;

  if (_currentVal == 0) {
    _delta = 0;
  } else {
    _delta = (255.0 - _currentVal) * PEEKVALUE / PEEKDEV;
  }
}

void VentilationControlClass::wait() {
  coolerSet(false);
  _on = false;
}

void VentilationControlClass::refresh() {
  if (_currentVal == 0) {
    coolerSet(false);
    _on = false;
    return;
  }

  // Почти полная мощность — держим включённым постоянно.
  if (_currentVal >= 255 || _delta < PEEKVALUE) {
    coolerSet(true);
    _on = true;
    return;
  }

  if (_on) {
    if (expired(_timer, PEEKVALUE)) {
      _timer = millis();
      _on = false;
      coolerSet(false);
    }
  } else {
    if (expired(_timer, static_cast<unsigned long>(_delta))) {
      _timer = millis();
      _on = true;
      coolerSet(true);
    }
  }
}
