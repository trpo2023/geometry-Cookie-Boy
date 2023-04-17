#include <ctest.h>

#include <parser.h>

CTEST(INPUT_FILE, CHECK_AMOUNT_STRINGS)
{
    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    ASSERT_EQUAL(3, readFile("data", figures, errmsg));
}