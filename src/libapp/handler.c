#include "handler.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void skipSpaces(char *string, Figure *figure, int *n)
{
    while (string[*n] == ' ')
    {
        figure->name[*n] = string[*n];
        (*n)++;
    }
}

void fillErrorString(char *string, int index, char *expect)
{
    int j;
    for (j = 0; j < index; j++)
        string[j] = ' ';

    char value[MIN_ELEMENTS];
    char *first = "^\nError at column ";
    char *second;
    if (!strlen(expect))
        second = ": unexpected token";
    else
        second = ": expected '";
    itoa(index, value, 10);

    for (int i = 0; i < strlen(first); i++, j++)
        string[j] = first[i];

    for (int i = 0; i < strlen(value); i++, j++)
        string[j] = value[i];

    for (int i = 0; i < strlen(second); i++, j++)
        string[j] = second[i];

    for (int i = 0; i < strlen(expect); i++, j++)
        string[j] = expect[i];

    if (strlen(expect) != 0)
    {
        string[j] = '\'';
        j++;
    }

    string[j] = '\0';
}

double getValue(char *string, int *n, Figure *figure, char el, char *errmsg)
{
    int i = *n;
    char axis[MIN_ELEMENTS];
    int j = 0;
    bool isDot = false;
    bool isMinus = false;

    while (string[i] != el)
    {
        figure->name[i] = string[i];
        figure->name[i + 1] = '\0';
        if (((string[i] >= '0') && (string[i] <= '9')) || (!isDot && (string[i] == '.')) || (!isMinus && (string[i] == '-')))
        {
            axis[j] = string[i];
            j++;
            if (string[i] == '.')
                isDot = true;
            else if (string[i] == '-')
                isMinus = true;
        }
        else
        {
            axis[j] = '\0';
            if ((strlen(axis) > 0) && ((axis[j - 1] != '.') || (axis[j - 1] != '-')))
            {
                char temp[2];
                temp[0] = el;
                temp[1] = '\0';
                fillErrorString(errmsg, i, temp);
                return 1;
            }
            fillErrorString(errmsg, i, "double");
            return 1;
        }
        i++;
    }

    *n = i;
    axis[j] = '\0';
    return atof(axis);
}

int circleHandler(char *string, Figure *figure, char *errmsg)
{
    char *elements = "( ,)";
    int i = CIRCLE_START; // т.к. "circle"
    int j = 0;

    skipSpaces(string, figure, &i);
    if (string[i] != elements[0])
    {
        fillErrorString(errmsg, i, "(");
        return 1;
    }
    figure->name[i] = elements[0];
    i++;

    for (int el = 1; el < strlen(elements); el++, i++)
    {
        skipSpaces(string, figure, &i);
        double value = getValue(string, &i, figure, elements[el], errmsg);
        if (strlen(errmsg) == 0)
        {
            figure->coords[j] = value;
            j++;
        }
        else
        {
            return 1;
        }
        figure->name[i] = string[i];
    }

    skipSpaces(string, figure, &i);
    if (string[i] != '\n')
    {
        fillErrorString(errmsg, i, "");
        return 1;
    }
    return i;
}

int triangleHandler(char *string, Figure *figure, char *errmsg)
{
    char *elements = "(( , , , ))";
    int i = TRIANGLE_START; // т.к. "triangle"
    int j = 0;

    if (string[i] != elements[0])
    {
        fillErrorString(errmsg, i, "(");
        return 1;
    }
    figure->name[i] = elements[0];
    i++;
    if (string[i] != elements[1])
    {
        fillErrorString(errmsg, i, "(");
        return 1;
    }
    figure->name[i] = elements[1];
    i++;

    for (int el = 2; el < strlen(elements) - 1; el++, i++)
    {
        skipSpaces(string, figure, &i);
        double value = getValue(string, &i, figure, elements[el], errmsg);
        if (strlen(errmsg) == 0)
        {
            figure->coords[j] = value;
            j++;
        }
        else
        {
            return 1;
        }
        figure->name[i] = string[i];
    }

    skipSpaces(string, figure, &i);
    if (string[i] != elements[strlen(elements) - 1])
    {
        fillErrorString(errmsg, i, ")");
        return 1;
    }
    figure->name[i] = string[i];
    i++;

    skipSpaces(string, figure, &i);
    if (string[i] != '\n')
    {
        fillErrorString(errmsg, i, "");
        return 1;
    }
    return i;
}

int stringHandler(char *string, Figure *figure, char *errmsg)
{
    for (int i = 0; i < strlen(string); i++)
    {
        figure->name[i] = '\0';
        if (!strcmp(figure->name, "circle"))
        {
            figure->figureType = 0;
            i = circleHandler(string, figure, errmsg);
            figure->name[i] = '\0';
            if (strlen(errmsg) != 0)
                return 1;
            return 0;
        }
        if (!strcmp(figure->name, "triangle"))
        {
            figure->figureType = 1;
            i = triangleHandler(string, figure, errmsg);
            figure->name[i] = '\0';
            if (strlen(errmsg) != 0)
                return 1;
            return 0;
        }
        else
        {
            string[i] = tolower(string[i]);
            figure->name[i] = string[i];
        }
    }

    fillErrorString(errmsg, 0, "circle' or 'triangle");
    return 1;
}
