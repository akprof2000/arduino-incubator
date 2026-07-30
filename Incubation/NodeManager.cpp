//
//
//

#include "NodeManager.h"

#include "Alerting.h"
#include "objects.h"
#include "timing.h"

NodeManagerClass NodeManager;

void NodeManagerClass::init() {
  _currentnode = Menuconfig.initstatus();
  _mainnode = _currentnode;
  _status = true;
  _show = false;
  _timing = millis();
  _timingsleep = _timing;
}

void NodeManagerClass::goTo(BaseNodeClass *node) {
  if (node == nullptr) return;
  _currentnode = node;
  _show = false;
}

void NodeManagerClass::goToStatus() {
  BaseNodeClass *node = Menuconfig.initstatus();
  Menuconfig.clearmenu();
  if (node != nullptr) {
    _currentnode = node;
    _mainnode = node;
  }
  _status = true;
  _show = false;
}

void NodeManagerClass::goToMenu() {
  BaseNodeClass *node = Menuconfig.initmenu();
  if (node == nullptr) return;  // не хватило памяти — остаёмся в статусе
  Menuconfig.clearstatus();
  _currentnode = node;
  _status = false;
  _show = false;
}

// ---------------------------------------------------------------------------
// Опрос кнопок
// ---------------------------------------------------------------------------
void NodeManagerClass::readButtons() {
  for (byte i = 0; i < BUTTON_COUNT; i++) {
    if (bouncer[i].update()) {
      // Любое нажатие «будит» подсветку.
      adjustments.setup(BRITHPIN, CONTRPIN, bright, 100 - contr);
      _timing = millis();
      _timingsleep = _timing;
      appl[i] = false;

      if (bouncer[i].read() == HIGH) {
        bState[i] = btn_up;
      } else {
        bState[i] = btn_down;
        bPressTime[i] = millis();
      }
    }

    if (bState[i] == btn_down) {
      _timingsleep = _timing;
      if (expired(bPressTime[i], PUSHINTERVAL)) {
        _timing = millis();
        bState[i] = btn_push;  // перешли в режим удержания
        appl[i] = false;
      }
    } else if (bState[i] == btn_push) {
      _timingsleep = _timing;
    }
  }
}

// ---------------------------------------------------------------------------
// Навигация
// ---------------------------------------------------------------------------
bool NodeManagerClass::navigate() {
  // Долгое удержание «назад» — сразу в корень (экраны статуса).
  // Раньше выйти из глубокого подменю можно было только пошагово
  // или дождавшись таймаута в минуту.
  if (bState[BTN_BACK] == btn_push && !appl[BTN_BACK]) {
    appl[BTN_BACK] = true;
    if (!_status) {
      goToStatus();
      return true;
    }
  }

  if (bState[BTN_BACK] == btn_down && !appl[BTN_BACK]) {
    appl[BTN_BACK] = true;
    bPressTime[BTN_BACK] = millis();

    if (_currentnode->getOwner() != nullptr) {
      if (_currentnode->allowOwner()) goTo(_currentnode->getOwner());
    } else if (_status) {
      goToMenu();
    } else {
      goToStatus();
    }
    return true;
  }

  if (bState[BTN_OK] == btn_down && !appl[BTN_OK]) {
    BaseNodeClass *inner = _currentnode->getInner();
    if (inner != nullptr) {
      if (_currentnode->allowInner()) {
        appl[BTN_OK] = true;
        goTo(inner);
      }
    } else if (_currentnode->exit && !_status) {
      appl[BTN_OK] = true;
      goToStatus();
    }
    return true;
  }

  if (bState[BTN_UP] == btn_down && !appl[BTN_UP]) {
    if (_currentnode->getNext() != nullptr && _currentnode->allowNext()) {
      appl[BTN_UP] = true;
      goTo(_currentnode->getNext());
    }
    return true;
  }

  if (bState[BTN_DOWN] == btn_down && !appl[BTN_DOWN]) {
    if (_currentnode->getPrev() != nullptr && _currentnode->allowPrev()) {
      appl[BTN_DOWN] = true;
      goTo(_currentnode->getPrev());
    }
    return true;
  }

  return false;
}

void NodeManagerClass::work() {
  readButtons();

  // Кнопка «OK» дополнительно глушит звук аварии.
  if (bState[BTN_OK] == btn_down) Alerting.BlockSound();

  navigate();

  // Бездействие: гасим подсветку и возвращаемся из меню в статус.
  if (expired(_timingsleep, MENUEXIT) || toroot) {
    if (!_status || toroot) {
      toroot = false;
      goToStatus();
      bPressTime[BTN_BACK] = millis();
      appl[BTN_BACK] = true;
    }
    _timingsleep = millis();
    adjustments.setup(BRITHPIN, CONTRPIN, 0, 100 - contr);
  }

  if (_currentnode == nullptr) return;

  if (!_show) {
    _timing = millis();
    _currentnode->deleteMenu();  // подменю пересоздаётся при входе
    _currentnode->show();
    _show = true;
  } else {
    if (_status && expired(_timing, DISPLAYINTERVAL)) {
      _timing = millis();
      _currentnode->renew();
    }

    if (expired(_timing, ENDINTERVAL)) {
      goTo(_mainnode);
    }
  }

  _currentnode->refresh();
}
