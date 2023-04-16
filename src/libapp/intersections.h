#pragma once

#include <stdbool.h>
#include <handler.h>

int max(int, int);
int min(int, int);
int area(Coords, Coords, Coords);
bool intersect_1(int, int, int, int);
bool differentFigures(Figure, Figure);
bool similarFigures(Figure, Figure);
int getIntersections(Figure *, int, int);
void printIntersections(Figure *, int, int);