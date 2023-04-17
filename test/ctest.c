#include <ctest.h>
#include <math.h>

#define _USE_MATH_DEFINES // M_PI in math.h

#include <parser.h>
#include <calculations.h>

CTEST(INPUT_FILE, CHECK_AMOUNT_STRINGS)
{
    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    ASSERT_EQUAL(3, readFile("data", figures, errmsg));
}

CTEST(INPUT_FILE, CHECK_CIRCLE_AREA)
{
    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    readFile("data", figures, errmsg);
    ASSERT_DBL_NEAR(M_PI * pow(figures[1].coords[0].radius, 2), circleArea(figures[1].coords));
}