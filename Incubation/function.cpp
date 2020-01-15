// 
// 
// 

#include "function.h"
#include "objects.h"


int StrLength(String str)
{
	byte i = 0, count = 0;

	while (str[i] != '\0')
	{
		if (str[i] < ' ')
			i = i + 2;
		else i++;
		count++;
	}
	return count;

}

String gettextprj(byte data)
{

	switch (data)
	{
	case 0:
		return F("");
	case 253:
		return F("Выход");
	case 1:
		return F("Основное");
	case 2:
		return F("меню");
	case 3:
		return F("Настройки");
	case 4:
		return F("схем");
	case 5:
		return F("Пороги аварийных");
	case 6:
		return F("режимов работы");
	case 7:
		return F("Прд:   День:");
	case 8:
		return F("пороги");
	case 9:
		return F("Дисплей");
	case 10:
		return F("Запуск");
	case 11:
		return F("цикла");
	case 12:
		return F("Куры");
	case 13:
		return F("Индейка");
	case 14:
		return F("Утки");
	case 15:
		return F("Индоутки");
	case 16:
		return F("Гуси");
	case 17:
		return F("Перепела");
	case 18:
		return F("День с    по ");
	case 19:
		return F("период: ");
	case 20:
		return F("Температура:   С");
	case 21:
		return F("Влажность:    %");
	case 22:
		return F("Поворот   р/c");
	case 23:
		return F("Поворот нет   ");
	case 24:
		return F("Прв.Х р/c по   м");
	case 25:
		return F("Прв.нет         ");
	case 26:
		return F("Яркость:     %");
	case 27:
		return F("Контраст:     %");
	case 28:
		return F("Температура С");
	case 29:
		return F("Длт:     Макс:");
	case 30:
		return F("Влажность в %");
	case 31:
		return F("Длт:     Макс:");
	case 32:
		return F("Период N 1");
	case 33:
		return F("Период N 2");
	case 34:
		return F("Период N 3");
	case 35:
		return F("Период N 4");
	case 36:
		return F("Охл.Х р/c по   м");
	case 37:
		return F("теплее     С");
	case 38:
		return F("Охл.нет         ");

	case 39:
		return F("Т у.:    т.:   ");

	case 40:
		return F("В у.:    т.:   ");
	case 41:
		return F("Аварийная");
	case 42:
		return F("Ситуация!!!");
	case 43:
		return F("Т1:     Т2:");
	case 44:
		return F("Т3:     Т4:");
	case 45:
		return F("Выберите режим");
	case 46:
		return F("и период старта");
	case 47:
		return F("Схема");
	case 48:
		return F("П.:  Д.:   ч.:  ");
	case 49:
		return F("Текущая операция");
	case 50:
		return F("Текущее событие");

	case 51:
		return F("Мин.нагрев:    %");
	case 52:
		return F("Мин.увл:    %");
	case 53:
		return F("Пороговые");
	case 54:
		return F("значения вкл.");

	case 100:
		return F("Действий нет");

	case 101:
		return F("Ничего на (");
	case 102:
		return F("Вытяжка");
	case 103:
		return F("Нагрев (");
	case 104:
		return F("Выдув (");
	case 105:
		return F("Испаритель (");
	case 106:
		return F("Вытяжка (");
	case 107:
		return F("Поворот");
	case 108:
		return F("Обслуживание");
	case 109:
		return F("Дверь открыта!!!");
	case 110:
		return F("    ");
	case 111:
		return F("Отклонений нет");


	case 150:
		return F("Дверь открыта!!!");
	case 151:
		return F("Текущий план выполнен!");
	case 152:
		return F("Расхождение по температуре!!");
	case 153:
		return F("Расхождение по влажности!!");


	case 200:
		return F("Текущая схема: ");
	case 201:
		return F(", период: ");
	case 202:
		return F(", день: ");
	case 203:
		return F(", час: ");
	case 204:
		return F("Температура: Установленная: ");
	case 205:
		return F(", текущая: ");
	case 206:
		return F("Влажность: Установленная: ");

	case 207:
		return F("Температура: ");

	case 208:
		return F("Датчик N1: ");
	case 209:
		return F("; Датчик N2: ");
	case 210:
		return F("; Датчик N3: ");
	case 211:
		return F("; Датчик N4: ");
	case 212:
		return F(": ");
	case 213:
		return F(", время: ");


	case 240:
		return F("%)");
	case 249:
		return F("----");
	case 250:
		return F("    ");
	case 251:
		return F("  ");
	case 252:
		return F("   ");

	case 255:
		return F("Статус");

	default:

		break;
	}

	return F("");

}




BaseNodeClass **createListMenu(byte size)
{
	BaseNodeClass ** listMenu = new BaseNodeClass*[size];
	for (byte i = 0; i < size; i++)
	{
		listMenu[i] = NULL;
	}
	return listMenu;
}

void deleteListMenu(byte size, BaseNodeClass **listMenu) noexcept
{
	if (listMenu != NULL)
	{
		for (byte i = 0; i < size; i++)
		{
			delete listMenu[i];
		}
		delete[] listMenu;
	}
}


bool scrollBar(float minval, float maxval, float curstep, float &val)
{
	if (bState[1] == btn_down && appl[1] == false)
	{
		val += curstep;
		if (val > maxval)
			val = maxval;
		appl[1] = true;
		return true;
	}
	if (bState[2] == btn_down && appl[2] == false)
	{
		val -= curstep;
		if (val < minval)
			val = minval;
		appl[2] = true;
		return true;
	}

	if (bState[1] == btn_push && appl[1] == false)
	{
		delay(SCROLLDELAY);
		val += curstep;
		if (val > maxval)
			val = maxval;
		return true;
	}
	if (bState[2] == btn_push && appl[2] == false)
	{
		delay(SCROLLDELAY);
		val -= curstep;
		if (val < minval)
			val = minval;
		return true;
	}

}

void baseShowData(int len, String str1, String str2)
{
	lcd.clear();
	for (byte i = 0; i < len; i++)
	{
		String str = i == 0 ? str1 : str2;
		byte l = (LCDCOLS - StrLength(str)) >> 1;
		/*		if (l != 0 && l % 2 == 0)
				{
					l--;
				}
			*/	lcd.setCursor(l, i);
		lcd.print(str);
	}
}