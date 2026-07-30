// StatusInfo.h

#ifndef _STATUSINFO_h
#define _STATUSINFO_h

#include <Arduino.h>

#include "texts.h"

enum StatusOper : uint8_t {
  so_none = 0,   // «Ничего на (N%)»
  so_blow = 1,   // вытяжка (проветривание)
  so_heet = 2,   // нагрев
  so_cool = 3,   // выдув (охлаждение)
  so_wet = 4,    // испаритель
  so_dry = 5,    // вытяжка по влажности
  so_rot = 6,    // поворот лотка
  so_cent = 7,   // центрирование лотка
  so_door = 8,   // дверь открыта
  so_count = 9
};

// Текущая «занятость» исполнительных устройств в процентах.
class StatusInfoClass {
 public:
  void AddStatus(StatusOper status, double fill);
  // БЫЛО: String Print() — строка собиралась конкатенацией в куче
  // и возвращалась по значению на каждой отрисовке экрана.
  void Print(TextBuilder &builder) const;

 private:
  uint8_t _oper[so_count] = {0};
};

extern StatusInfoClass StatusInfo;

#endif
