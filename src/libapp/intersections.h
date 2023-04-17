#pragma once

#include <stdbool.h>
#include <parser.h>

int max(int, int);
int min(int, int);
int area(Coords, Coords, Coords);
bool boundingBox(int, int, int, int);
bool similarFigures(Figure, Figure);
bool differentFigures(Figure, Figure);
int getIntersections(Figure *, int, int);
void printIntersections(Figure *, int, int);