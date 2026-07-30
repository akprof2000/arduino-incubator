//
// Таблица строк интерфейса. Всё лежит во FLASH.
//

#include "texts.h"

// Каждая строка — отдельный массив в PROGMEM.
#define TXT(name, value) static const char name[] PROGMEM = value

TXT(s_empty, "");

TXT(s001, "Основное");
TXT(s002, "меню");
TXT(s003, "Настройки");
TXT(s004, "схем");
TXT(s005, "Пороги аварийных");
TXT(s006, "режимов работы");
TXT(s007, "Прд:   День:");
TXT(s008, "пороги");
TXT(s009, "Дисплей");
TXT(s010, "Запуск");
TXT(s011, "цикла");
TXT(s012, "Куры");
TXT(s013, "Индейка");
TXT(s014, "Утки");
TXT(s015, "Индоутки");
TXT(s016, "Гуси");
TXT(s017, "Перепела");
TXT(s018, "День с    по ");
TXT(s019, "период: ");
TXT(s020, "Температура:   С");
TXT(s021, "Влажность:    %");
TXT(s022, "Поворот   р/c");
TXT(s023, "Поворот нет   ");
TXT(s024, "Прв.Х р/c по   м");
TXT(s025, "Прв.нет         ");
TXT(s026, "Яркость:     %");
TXT(s027, "Контраст:     %");
TXT(s028, "Температура С");
TXT(s029, "Длт:     Макс:");
TXT(s030, "Влажность в %");
TXT(s031, "Длт:     Макс:");
TXT(s032, "Период N 1");
TXT(s033, "Период N 2");
TXT(s034, "Период N 3");
TXT(s035, "Период N 4");
TXT(s036, "Охл.Х р/c по   м");
TXT(s037, "теплее     С");
TXT(s038, "Охл.нет         ");
TXT(s039, "Т у.:    т.:    ");
TXT(s040, "В у.:    т.:    ");
TXT(s041, "Аварийная");
TXT(s042, "Ситуация!!!");
TXT(s043, "Т1:     Т2:     ");
TXT(s044, "Т3:     Т4:     ");
TXT(s045, "Выберите режим");
TXT(s046, "и период старта");
TXT(s047, "Схема           ");
TXT(s048, "П.:  Д.:   ч.:  ");
TXT(s049, "Текущая операция");
TXT(s050, "Текущее событие ");
TXT(s051, "Мин.нагрев:    %");
TXT(s052, "Мин.увл:    %");
TXT(s053, "Пороговые");
TXT(s054, "значения вкл.");
TXT(s055, "Мин. дел.Т1:    ");
TXT(s056, "Макс.дел.Т1:    ");

TXT(s100, "Действий нет");
TXT(s101, "Ничего на (");
TXT(s102, "Вытяжка");
TXT(s103, "Нагрев (");
TXT(s104, "Выдув (");
TXT(s105, "Испаритель (");
TXT(s106, "Вытяжка (");
TXT(s107, "Поворот");
TXT(s108, "Центрирование");
TXT(s109, "Дверь открыта!!!");
TXT(s110, "    ");
TXT(s111, "Отклонений нет");
TXT(s112, "                ");

TXT(s150, "Дверь открыта!!!");
TXT(s151, "Текущий план выполнен!");
TXT(s152, "Расхождение по температуре!!");
TXT(s153, "Расхождение по влажности!!");
TXT(s154, "Ошибка основного датчика!!");

TXT(s200, "Текущая схема: ");
TXT(s201, ", период: ");
TXT(s202, ", день: ");
TXT(s203, ", час: ");
TXT(s204, "Температура: Установленная: ");
TXT(s205, ", текущая: ");
TXT(s206, "Влажность: Установленная: ");
TXT(s207, "Температура: ");
TXT(s208, "Датчик N1: ");
TXT(s209, "; Датчик N2: ");
TXT(s210, "; Датчик N3: ");
TXT(s211, "; Датчик N4: ");
TXT(s212, ": ");
TXT(s213, ", время: ");

TXT(s240, "%)");
TXT(s249, "----");
TXT(s250, "    ");
TXT(s251, "  ");
TXT(s252, "   ");
TXT(s253, "Выход");
TXT(s255, "Статус");

// ---------------------------------------------------------------------------
// Плотная таблица: id -> смещение в блоке. Идентификаторы разрежены
// (0..56, 100..112, 150..154, 200..213, 240..255), поэтому вместо массива
// на 256 указателей (512 байт FLASH и лишний расход) используются
// диапазоны — так же быстро (O(1)) и компактнее.
// ---------------------------------------------------------------------------

static const char *const BLOCK_0[] PROGMEM = {
    s_empty, s001, s002, s003, s004, s005, s006, s007, s008, s009,
    s010,    s011, s012, s013, s014, s015, s016, s017, s018, s019,
    s020,    s021, s022, s023, s024, s025, s026, s027, s028, s029,
    s030,    s031, s032, s033, s034, s035, s036, s037, s038, s039,
    s040,    s041, s042, s043, s044, s045, s046, s047, s048, s049,
    s050,    s051, s052, s053, s054, s055, s056};

static const char *const BLOCK_100[] PROGMEM = {
    s100, s101, s102, s103, s104, s105, s106,
    s107, s108, s109, s110, s111, s112};

static const char *const BLOCK_150[] PROGMEM = {s150, s151, s152, s153, s154};

static const char *const BLOCK_200[] PROGMEM = {
    s200, s201, s202, s203, s204, s205, s206,
    s207, s208, s209, s210, s211, s212, s213};

static const char *const BLOCK_240[] PROGMEM = {
    s240,    s_empty, s_empty, s_empty, s_empty, s_empty, s_empty, s_empty,
    s_empty, s249,    s250,    s251,    s252,    s253,    s_empty, s255};

// Возвращает указатель на PROGMEM-строку (сырой const char*).
static const char *rawText(uint8_t id) {
  const char *const *table;
  uint8_t index;

  if (id <= 56) {
    table = BLOCK_0;
    index = id;
  } else if (id >= 100 && id <= 112) {
    table = BLOCK_100;
    index = id - 100;
  } else if (id >= 150 && id <= 154) {
    table = BLOCK_150;
    index = id - 150;
  } else if (id >= 200 && id <= 213) {
    table = BLOCK_200;
    index = id - 200;
  } else if (id >= 240) {
    table = BLOCK_240;
    index = id - 240;
  } else {
    return s_empty;
  }

  return reinterpret_cast<const char *>(pgm_read_ptr(&table[index]));
}

const __FlashStringHelper *T(uint8_t id) {
  return reinterpret_cast<const __FlashStringHelper *>(rawText(id));
}

uint8_t TLen(uint8_t id) {
  const char *p = rawText(id);
  uint8_t count = 0;
  for (;;) {
    uint8_t c = pgm_read_byte(p++);
    if (c == 0) break;
    // Продолжающие байты UTF-8 (10xxxxxx) не занимают знакоместо.
    if ((c & 0xC0) != 0x80) count++;
  }
  return count;
}

void TextBuilder::addP(uint8_t id) {
  const char *src = rawText(id);
  for (;;) {
    if (_pos >= _end) break;
    const char c = static_cast<char>(pgm_read_byte(src++));
    if (c == '\0') break;
    *_pos++ = c;
  }
  *_pos = '\0';
}

void TextBuilder::add(const char *text) {
  if (text == nullptr) return;
  while (*text && _pos < _end) *_pos++ = *text++;
  *_pos = '\0';
}

void TextBuilder::add(unsigned int value) {
  char digits[6];
  uint8_t n = 0;
  do {
    digits[n++] = static_cast<char>('0' + (value % 10));
    value /= 10;
  } while (value != 0 && n < sizeof(digits));

  while (n > 0 && _pos < _end) *_pos++ = digits[--n];
  *_pos = '\0';
}

void TextBuilder::addSeparator() {
  if (empty()) return;
  add("; ");
}

uint8_t strLenLcd(const char *s) {
  if (s == nullptr) return 0;
  uint8_t count = 0;
  while (*s) {
    if ((static_cast<uint8_t>(*s) & 0xC0) != 0x80) count++;
    s++;
  }
  return count;
}
