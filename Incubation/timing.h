// timing.h
//
// Корректная работа с millis().
//
// По всему проекту раньше использовалась конструкция
//     if (abs(millis() - _timer) > INTERVAL)
// с двумя проблемами:
//
//  1) `abs()` в Arduino — это МАКРОС `((x)>0?(x):-(x))`, который вычисляет
//     аргумент дважды. То есть millis() вызывался два раза подряд и мог
//     вернуть разные значения — редкий, но реальный источник «дёрганья».
//  2) Для беззнаковой арифметики abs() бессмысленен: millis() - t уже
//     даёт корректный результат при переполнении счётчика (~49.7 суток).
//     А вот сам abs() на unsigned long ломает знаковое сравнение.
//
// elapsed() решает обе проблемы: один вызов millis(), корректное
// переполнение, понятное имя.

#ifndef _TIMING_h
#define _TIMING_h

#include <Arduino.h>

// Сколько миллисекунд прошло с момента `since`. Корректно при переполнении.
inline unsigned long elapsed(unsigned long since) { return millis() - since; }

// Прошло ли не менее `interval` мс с момента `since`.
inline bool expired(unsigned long since, unsigned long interval) {
  return elapsed(since) >= interval;
}

#endif
