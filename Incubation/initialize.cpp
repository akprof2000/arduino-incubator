// 
// 
// 

#include "initialize.h"
#include "consts.h"
#include "objects.h"

bool InitializeClass::init()
{
	if (shift > 0 && millis() < timer + PROGRESSINT)
	{
		return true;
	}
	timer = millis();

	switch (shift) {
	case 0:
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Загрузка");
		break;
	case 1:
		lcd.setCursor(0, 1);
		lcd.write(byte(1));
		break;
	case 2:
		lcd.setCursor(0, 1);
		lcd.write(byte(2));
		break;
	case 3:
		lcd.setCursor(0, 1);
		lcd.write(byte(3));
		break;
	case 4:
		lcd.setCursor(1, 1);
		lcd.write(byte(4));
		break;
	case 5:
		lcd.setCursor(1, 1);
		lcd.write(byte(5));
		break;
	case 6:
		lcd.setCursor(1, 1);
		lcd.write(byte(6));
		break;
	case 7:
		lcd.setCursor(2, 1);
		lcd.write(byte(7));
	default:
		shift = -1;
		
		return false;		
	}

	shift++;

	return true;

}


InitializeClass Initialize;




