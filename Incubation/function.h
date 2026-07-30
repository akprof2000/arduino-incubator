// function.h
//
// Общие помощники отрисовки и ввода.

#ifndef _FUNCTION_h
#define _FUNCTION_h

#include <Arduino.h>

#include "BaseNode.h"
#include "texts.h"

// Прокрутка значения кнопками «вверх»/«вниз».
// Возвращает true, если значение изменилось.
bool scrollBar(float minval, float maxval, float curstep, float &val);

// Очистить экран и вывести две строки (из FLASH) по центру.
void showTwoLines(uint8_t id1, uint8_t id2);

// Очистить экран и вывести одну строку по центру верхней строки.
void showOneLine(uint8_t id);

// Вывести C-строку по центру указанной строки дисплея (без очистки).
void printCentered(uint8_t row, const char *text);

// Дописать пробелы до колонки `column` — чтобы не оставался «хвост»
// от предыдущего, более длинного значения.
void padTo(uint8_t from, uint8_t to);

// Массив дочерних узлов меню.
BaseNodeClass **createListMenu(byte size);
void deleteListMenu(byte size, BaseNodeClass **listMenu);

#endif
