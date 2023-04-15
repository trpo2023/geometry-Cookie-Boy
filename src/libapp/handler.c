#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <handler.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int area(Coords a, Coords b, Coords c) 
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
 
bool intersect_1(int a, int b, int c, int d) {
	if (a > b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    if (c > d)
    {
        int temp = c;
        c = d;
        d = temp;
    }
	return max(a, c) <= min(b, d);
}

bool differentFigures(Figure current, Figure figure)
{
    Coords *circleCoords, *triangleCoords;
    if (!strcmp(current.type, "circle"))
    {
        circleCoords = current.coords;
        triangleCoords = figure.coords;
    }
    else if (!strcmp(current.type, "triangle"))
    {
        circleCoords = figure.coords;
        triangleCoords = current.coords;
    }

    for (int i = 1; i < MAX_COORDS; i++)
    {
        Coords AB, OB;
        AB.x = triangleCoords[i].x - triangleCoords[i - 1].x;
        AB.y = triangleCoords[i].y - triangleCoords[i - 1].y;
        OB.x = triangleCoords[i].x - circleCoords[0].x;
        OB.y = triangleCoords[i].y - circleCoords[0].y;
        double AB_OB = (OB.x * OB.y) + (AB.x * AB.y);
        double AB_2 = AB.x * AB.x + AB.y * AB.y;
        double OB_2 = OB.x * OB.x + OB.y * OB.y;
        double t = (AB_OB + sqrt((AB_OB * AB_OB) - (AB_2 * (OB_2 - (circleCoords[0].radius * circleCoords[0].radius))))) / AB_2;

        double t_2 = (AB_OB - sqrt((AB_OB * AB_OB) - (AB_2 * (OB_2 - (circleCoords[0].radius * circleCoords[0].radius))))) / AB_2;
        
        // printf("%f | %f\n", t, triangleCoords[i].x);
        // printf("%f | %f\n", t_2, triangleCoords[i].x);

        if (((t > 0) && (t < 1)) || ((t_2 > 0) && (t_2 < 1)))
            return true;
    }
    return false;
}

bool similarFigures(Figure current, Figure figure)
{
    Coords *f_coords = current.coords;
    Coords *s_coords = figure.coords;
    if (!strcmp(current.type, "circle"))
    {
        double length = sqrt(pow(abs((f_coords[0].x - s_coords[0].x)), 2) + pow(abs((f_coords[0].y - s_coords[0].y)), 2));
        double r_sum = f_coords[0].radius + s_coords[0].radius;
        return length < r_sum;
    }
    else if (!strcmp(current.type, "triangle"))
    {
        for (int i = 0; i < MAX_COORDS - 1; i++)
        {
            Coords a = current.coords[i];
            Coords b = current.coords[i + 1];
            for (int j = 0; j < MAX_COORDS - 1; j++)
            {
                Coords c = figure.coords[j];
                Coords d = figure.coords[j + 1];
                if (intersect_1 (a.x, b.x, c.x, d.x) && intersect_1 (a.y, b.y, c.y, d.y) && (area(a,b,c) * area(a,b,d) <= 0) && (area(c,d,a) * area(c,d,b) <= 0))
                return true;
            }
        }
    }
    return false;
}

int getIntersections(Figure *figures, int current, int total)
{
    char *currentType = figures[current].type;
    int j = 0;

    for (int i = 0; i < total; i++)
    {
        if (i != current)
        {
            char *figureType = figures[i].type;
            if (!strcmp(currentType, figureType))
            {
                if (similarFigures(figures[current], figures[i]))
                {
                    figures[current].intersects[j] = i + 1;
                    j++;
                }
            }
            else
            {
                if (differentFigures(figures[current], figures[i]))
                {
                    figures[current].intersects[j] = i + 1;
                    j++; 
                }
            }
        }
    }
    figures[current].intersects[j] = 0;
    return j;
}

double circlePerimeter(Coords *coords)
{
    return 2 * M_PI * coords[0].radius;
}

double trianglePerimeter(Coords *coords)
{
    int n = MAX_COORDS;
    if ((coords[0].x != coords[n - 1].x) || (coords[0].y != coords[n - 1].y))
    {
        return -1;
    }

    double sum = 0;
    for (int i = 1; i < n; i++)
    {
        sum += sqrt(pow((coords[i].x - coords[i - 1].x), 2) + pow((coords[i].y - coords[i - 1].y), 2));
    }

    return sum;
}

double circleArea(Coords *coords)
{
    return M_PI * (coords[0].radius * coords[0].radius);
}

double triangleArea(Coords *coords, double halfPerimeter)
{
    int n = MAX_COORDS;
    if ((coords[0].x != coords[n - 1].x) || (coords[0].y != coords[n - 1].y))
    {
        return -1;
    }

    double prod = halfPerimeter;
    for (int i = 1; i < n; i++)
    {
        prod *= halfPerimeter - sqrt(pow((coords[i].x - coords[i - 1].x), 2) + pow((coords[i].y - coords[i - 1].y), 2));
    }

    return sqrt(prod);
}

void addSpaces(int n)
{
    for (int i = 0; i < n; i++)
        printf(" ");
}

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
    sprintf(value, "%d", index);

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
        if (((string[i] >= '0') && (string[i] <= '9')) || (!isDot && (string[i] == '.')) ||
            (!isMinus && (string[i] == '-')))
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
    int count = 0;

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
            if (!count)
            {
                figure->coords[j].x = value;
                count++;
            }
            else if (count == 1)
            {
                figure->coords[j].y = value;
                count++;
            }
            else if (count == 2)
            {
                figure->coords[j].radius = value;
                j++;
                count++;
            }
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
    bool isX = true;

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
            if (isX)
            {
                figure->coords[j].x = value;
                isX = false;
                printf("%f\n", figure->coords[j].x);
            }
            else
            {
                figure->coords[j].y = value;
                isX = true;
                printf("%f\n", figure->coords[j].y);
                j++;
            }
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
            strcpy(figure->type, "circle");
            i = circleHandler(string, figure, errmsg);
            figure->name[i] = '\0';
            if (strlen(errmsg) != 0)
                return 1;
            return 0;
        }
        if (!strcmp(figure->name, "triangle"))
        {
            strcpy(figure->type, "triangle");
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
