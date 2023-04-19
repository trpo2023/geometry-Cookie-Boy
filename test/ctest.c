#include <ctest.h>
#include <math.h>
#include <stdio.h>

#define _USE_MATH_DEFINES // M_PI in math.h

#include <lexer.h>
#include <parser.h>

// Проверяет, сколько строк файла удалось прочитать
CTEST(INPUT_FILE, CHECK_AMOUNT_STRINGS)
{
    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    errmsg[0] = '\0';
    ASSERT_EQUAL(3, readFile("data.txt", figures, errmsg));
}