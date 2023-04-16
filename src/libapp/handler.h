#pragma once

#define MAX_ELEMENTS 255
#define MIN_ELEMENTS 10
#define CIRCLE_START 6
#define TRIANGLE_START 8
#define MAX_COORDS 4

typedef struct
{
    double x;
    double y;
    double radius;
} Coords;

typedef struct
{
    char name[MAX_ELEMENTS];
    char type[MIN_ELEMENTS];
    Coords coords[MAX_COORDS];
    int intersects[MIN_ELEMENTS];
} Figure;

void addSpaces(int);
void skipSpaces(char *, Figure *, int *);
void fillErrorString(char *, int, char *);
double getValue(char *, int *, Figure *, char, char *);
int circleHandler(char *, Figure *, char *);
int triangleHandler(char *, Figure *, char *);
int stringHandler(char *, Figure *, char *);
