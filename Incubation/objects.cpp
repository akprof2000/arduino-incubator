// 
// 
// 

#include "objects.h"

bool appl[4];
bool toroot;
ButtonState bState[4];
unsigned long bPressTime[4];
byte minheat;
byte minhum;

byte bright;
byte contr;
byte alTmpDel;
byte alTmpMax;
byte alHumDel;
byte alHumMax;

byte currentDay;
byte currentHour;
byte currentPeriod;
byte currentTable;
byte started;
byte timerUpdated;

bool allertEnable;
Bounce bouncer[4] = { pinbounced0, pinbounced1, pinbounced2, pinbounced3 };
LiquidCrystalRus lcd(LCDRS, LCDE, LCDD4, LCDD5, LCDD6, LCDD7);
LCDAdjustments adjustments;
DataRowClass currentRow;
HTU21D myHumidity;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float currentTemp;
float currentHumd;
float currentSetTemp;





