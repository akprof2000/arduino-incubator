//
//
//

#include "EditNode.h"

#include "consts.h"
#include "objects.h"
#include "timing.h"

void EditNodeClass::refresh() {
  if (bState[BTN_OK] == btn_down && !appl[BTN_OK]) {
    appl[BTN_OK] = true;

    _shift = nextField(_shift);
    if (_shift > _fieldCount) _shift = 0;

    commit();
    _blinc = false;
    drawFields();
    return;
  }

  if (!editing()) return;

  editField(_shift);

  if (expired(_timer, BLINKINTERVAL)) {
    _timer = millis();
    _blinc = !_blinc;
  }
  drawFields();
}
