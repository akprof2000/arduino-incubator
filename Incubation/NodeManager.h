// NodeManager.h

#ifndef _NODEMANAGER_h
#define _NODEMANAGER_h

#include <Arduino.h>

#include "menuconfig.h"
#include "node.h"

// Опрос кнопок, навигация по дереву экранов и вызов отрисовки.
class NodeManagerClass {
 public:
  void init();
  void work();

 private:
  BaseNodeClass *_currentnode = nullptr;
  BaseNodeClass *_mainnode = nullptr;
  unsigned long _timing = 0;
  unsigned long _timingsleep = 0;
  bool _status = true;  // true — показываем статус, false — меню
  bool _show = false;   // текущий экран уже отрисован

  void readButtons();
  bool navigate();
  void goToStatus();
  void goToMenu();
  void goTo(BaseNodeClass *node);
};

extern NodeManagerClass NodeManager;

#endif
