// texts.h
//
// Все строки интерфейса хранятся во FLASH (PROGMEM) и НИКОГДА не попадают
// в кучу. Раньше здесь использовалась функция `String gettextprj(byte)`,
// которая на каждый вызов создавала объект String -> malloc/free на каждой
// отрисовке экрана. Это и было основным источником фрагментации кучи
// и «плавающих» зависаний на ATmega.
//
// Теперь строка отдаётся как `const __FlashStringHelper*`, который
// Print::print() (а значит и lcd, и Serial) умеет печатать побайтово
// напрямую из FLASH — 0 байт RAM.

#ifndef _TEXTS_h
#define _TEXTS_h

#include <Arduino.h>

// ---------------------------------------------------------------------------
// Идентификаторы строк. Номера сохранены такими же, как в исходном проекте,
// чтобы не ломать арифметику вида T(12 + currentTable) / T(101 + i).
// ---------------------------------------------------------------------------
namespace Txt {
enum : uint8_t {
  Empty = 0,

  // --- меню -------------------------------------------------------------
  MainMenu1 = 1,        // "Основное"
  MainMenu2 = 2,        // "меню"
  SchemeSetup1 = 3,     // "Настройки"
  SchemeSetup2 = 4,     // "схем"
  AlarmSetup1 = 5,      // "Пороги аварийных"
  AlarmSetup2 = 6,      // "режимов работы"
  PeriodDay = 7,        // "Прд:   День:"
  Thresholds = 8,
  Display = 9,          // "Дисплей"
  StartCycle1 = 10,     // "Запуск"
  StartCycle2 = 11,     // "цикла"

  // Виды птицы: BirdFirst + currentTable (0..5)
  BirdFirst = 12,       // "Куры", "Индейка", "Утки", "Индоутки", "Гуси", "Перепела"

  DayFromTo = 18,       // "День с    по "
  Period = 19,          // "период: "
  Temperature = 20,     // "Температура:   С"
  Humidity = 21,        // "Влажность:    %"
  RotateOn = 22,        // "Поворот   р/c"
  RotateOff = 23,       // "Поворот нет   "
  VentOn = 24,          // "Прв.Х р/c по   м"
  VentOff = 25,         // "Прв.нет         "
  Brightness = 26,      // "Яркость:     %"
  Contrast = 27,        // "Контраст:     %"
  TempC = 28,           // "Температура С"
  DeltaMaxT = 29,       // "Длт:     Макс:"
  HumidityPct = 30,     // "Влажность в %"
  DeltaMaxH = 31,       // "Длт:     Макс:"

  // Периоды: PeriodFirst + type (0..3)
  PeriodFirst = 32,     // "Период N 1".."Период N 4"

  CoolOn = 36,          // "Охл.Х р/c по   м"
  Warmer = 37,          // "теплее     С"
  CoolOff = 38,         // "Охл.нет         "
  StatusT = 39,         // "Т у.:    т.:    "
  StatusH = 40,         // "В у.:    т.:    "
  Alarm1 = 41,          // "Аварийная"
  Alarm2 = 42,          // "Ситуация!!!"
  Temps12 = 43,         // "Т1:     Т2:     "
  Temps34 = 44,         // "Т3:     Т4:     "
  ChooseMode1 = 45,     // "Выберите режим"
  ChooseMode2 = 46,     // "и период старта"
  Scheme = 47,          // "Схема           "
  PDH = 48,             // "П.:  Д.:   ч.:  "
  CurrentOp = 49,       // "Текущая операция"
  CurrentEvent = 50,    // "Текущее событие "
  MinHeat = 51,         // "Мин.нагрев:    %"
  MinHum = 52,          // "Мин.увл:    %"
  TrigVals1 = 53,       // "Пороговые"
  TrigVals2 = 54,       // "значения вкл."
  EggDeltaMin = 55,     // "Мин. дел.Т1:    "
  EggDeltaMax = 56,     // "Макс.дел.Т1:    "

  // --- операции (StatusInfo): OperFirst + StatusOper --------------------
  NoActions = 100,      // "Действий нет"
  OperFirst = 101,      // 101..109 — по одной строке на StatusOper
  NoDeviations = 111,   // "Отклонений нет"
  Blank16 = 112,        // 16 пробелов (поля прокрутки)

  // --- аварии (Alerting): AlertFirst + AlertingType ---------------------
  AlertFirst = 150,     // 150..154

  // --- вывод в Serial ---------------------------------------------------
  LogScheme = 200,
  LogPeriod = 201,
  LogDay = 202,
  LogHour = 203,
  LogTempSet = 204,
  LogCurrent = 205,
  LogHumSet = 206,
  LogTemp = 207,
  LogSensor1 = 208,
  LogSensor2 = 209,
  LogSensor3 = 210,
  LogSensor4 = 211,
  LogColon = 212,
  LogTime = 213,

  PctClose = 240,       // "%)"
  Dashes = 249,         // "----"
  Blank4 = 250,
  Blank2 = 251,
  Blank3 = 252,
  Exit = 253,           // "Выход"
  Status = 255          // "Статус"
};
}  // namespace Txt

// Строка из FLASH по идентификатору. Для неизвестного id вернёт "".
const __FlashStringHelper *T(uint8_t id);

// Длина строки в ЗНАКОМЕСТАХ дисплея (а не в байтах): UTF-8 кириллица
// занимает 2 байта, но одно знакоместо HD44780.
uint8_t TLen(uint8_t id);

// Та же длина, но для обычной C-строки в RAM.
uint8_t strLenLcd(const char *s);

// ---------------------------------------------------------------------------
// Безопасная сборка строки в фиксированный буфер.
//
// Заменяет конкатенацию Arduino String (`res += curr;`), которая на каждом
// шаге делала realloc и была основным источником фрагментации кучи
// в StatusInfo::Print() и Alerting::Print().
//
// Переполнение невозможно: лишнее просто отбрасывается, строка всегда
// завершена нулём.
// ---------------------------------------------------------------------------
class TextBuilder {
 public:
  TextBuilder(char *buffer, uint8_t size)
      : _begin(buffer), _pos(buffer), _end(buffer + size - 1) {
    *_pos = '\0';
  }

  void addP(uint8_t id);            // строка из FLASH по идентификатору
  void add(const char *text);       // строка из RAM
  void add(unsigned int value);     // целое число
  void addSeparator();              // "; " — только если что-то уже есть

  bool empty() const { return _pos == _begin; }
  uint8_t length() const { return static_cast<uint8_t>(_pos - _begin); }

 private:
  char *const _begin;
  char *_pos;
  char *const _end;  // указывает на место под завершающий '\0'
};

#endif
