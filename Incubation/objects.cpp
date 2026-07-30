//
// Единственные определения глобальных объектов.
//

#include "objects.h"

// Порядок в массиве важен и используется во всём проекте:
//   0 — «влево»  (OK / подтверждение)
//   1 — «вверх»  (следующий пункт / увеличить)
//   2 — «вправо» (предыдущий пункт / уменьшить)
//   3 — «вниз»   (назад / выход)
Bounce bouncer[BUTTON_COUNT] = {Bounce(BUTTON_L, INTERVAL), Bounce(BUTTON_U, INTERVAL),
                                Bounce(BUTTON_R, INTERVAL), Bounce(BUTTON_D, INTERVAL)};

ButtonState bState[BUTTON_COUNT];
bool appl[BUTTON_COUNT];
unsigned long bPressTime[BUTTON_COUNT];
bool toroot = false;

byte bright = 50;
byte contr = 90;
byte minheat = 15;
byte minhum = 15;
byte deltaEggMin = 5;
byte deltaEggMax = 30;
byte alTmpDel = 1;
byte alTmpMax = 2;
byte alHumDel = 5;
byte alHumMax = 15;

byte currentDay = 1;
byte currentHour = 0;
byte currentPeriod = 0;
byte currentTable = 0;
byte started = 0;
byte timerUpdated = 1;

LiquidCrystalRus lcd(LCDRS, LCDE, LCDD4, LCDD5, LCDD6, LCDD7);
LCDAdjustments adjustments;
DataRowClass currentRow;
HTU21D myHumidity;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float currentTemp = 0;
float currentFirstTemp = 0;
// Пока датчик ни разу не опрошен, значение считается недостоверным —
// иначе первую секунду после включения регулятор увлажнения видел бы 0 %
// и сразу включал испаритель.
float currentHumd = 999;
float currentSetTemp = 0;

bool humidityValid(float value) { return value < HUM_INVALID; }
