// consts.h
//
// Распиновка и константы времени. Пины НЕ менялись — они привязаны
// к существующей плате.

#ifndef _CONSTS_h
#define _CONSTS_h

#include <Arduino.h>

// ---------------------------------------------------------------------------
// Кнопки
// ---------------------------------------------------------------------------
constexpr uint8_t BUTTON_COUNT = 4;

constexpr auto BUTTON_L = A15;  // 0 — OK / подтвердить
constexpr auto BUTTON_U = A13;  // 1 — вверх / увеличить
constexpr auto BUTTON_R = A12;  // 2 — вниз по списку / уменьшить
constexpr auto BUTTON_D = A14;  // 3 — назад / выход

// Индексы в массивах bouncer[] / bState[] / appl[]
constexpr uint8_t BTN_OK = 0;
constexpr uint8_t BTN_UP = 1;
constexpr uint8_t BTN_DOWN = 2;
constexpr uint8_t BTN_BACK = 3;

// ---------------------------------------------------------------------------
// Индикация аварии
// ---------------------------------------------------------------------------
constexpr auto RESETLEDPIN = 5;
constexpr auto ALARMLEDPIN = 5;
constexpr auto ALARMSOUNDPIN = 6;

// ---------------------------------------------------------------------------
// Лоток и дверь
// ---------------------------------------------------------------------------
constexpr auto DOOREPIN = A10;
constexpr auto TRAYLEFTPIN = 17;
constexpr auto TRAYRIGHTPIN = 18;
constexpr auto TRAYCENTERPIN = A11;

// ---------------------------------------------------------------------------
// Исполнительные устройства
// ---------------------------------------------------------------------------
constexpr auto HEATCONTROL = 2;  // ТЭН (ШИМ)
constexpr auto FANPIN = 4;       // испаритель
constexpr auto COOLERPIN = 3;    // вентилятор обдува/вытяжки

// ---------------------------------------------------------------------------
// Дисплей
// ---------------------------------------------------------------------------
constexpr auto LCDCOLS = 16;
constexpr auto LCDROWS = 2;

constexpr auto BRITHPIN = 7;
constexpr auto CONTRPIN = A1;

constexpr auto LCDRS = 13;
constexpr auto LCDE = 12;
constexpr auto LCDD4 = 11;
constexpr auto LCDD5 = 10;
constexpr auto LCDD6 = 9;
constexpr auto LCDD7 = 8;

// ---------------------------------------------------------------------------
// Датчики температуры
// ---------------------------------------------------------------------------
constexpr auto ONE_WIRE_BUS = 19;
constexpr auto TEMPERATURE_PRECISION = 11;
constexpr uint8_t MAX_TEMP_SENSORS = 4;  // столько помещается на экран

// ---------------------------------------------------------------------------
// Программная «мягкая» ШИМ вентилятора (период и дискретность)
// ---------------------------------------------------------------------------
constexpr auto PEEKVALUE = 5000;
constexpr auto PEEKDEV = 100;
constexpr auto VENTDEFROTATE = 255;

// ---------------------------------------------------------------------------
// Интервалы, мс
// ---------------------------------------------------------------------------
constexpr auto ROTATEVENT = 40000;      // длительность поворота лотка
constexpr auto INTERVAL = 9;            // антидребезг кнопок
constexpr auto PUSHINTERVAL = 1000;     // удержание -> автоповтор
constexpr auto SCROLLDELAY = 50;
constexpr auto DISPLAYINTERVAL = 3000;  // период обновления экрана статуса
constexpr auto ENDINTERVAL = 300000;    // возврат к главному экрану
constexpr auto MENUEXIT = 60000;        // выход из меню по бездействию
constexpr auto REFRESHS_SROLL = 300;    // шаг прокрутки значения
constexpr auto BLINKINTERVAL = 500;     // мигание редактируемого поля
constexpr auto RESETINTERVAL = 5000;    // удержание кнопки для сброса EEPROM
constexpr auto ERRORINTERVAL = 500;     // период мигания аварийной индикации
constexpr auto REFRESHDATA = 1000;      // период опроса датчиков
constexpr auto SCROLLSPEED = 250;       // скорость бегущей строки

constexpr auto WAITAFTEREVENT = 180000;  // «тишина» после события, мс
constexpr auto WAITOPENDOOR = 180000;    // допустимое время открытой двери

// ---------------------------------------------------------------------------
// Базовые смещения хранения уставок (значение = BASE + сохранённый байт)
// ---------------------------------------------------------------------------
constexpr auto BASETEMP = 30;  // °C
constexpr auto BASEHUM = 45;   // %

// HTU21D возвращает 998/999 при ошибке шины.
constexpr float HUM_INVALID = 100.0f;

#endif
