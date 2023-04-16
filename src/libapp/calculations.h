#pragma once

#include <handler.h>

#define _USE_MATH_DEFINES // M_PI in math.h

double circlePerimeter(Coords *);
double trianglePerimeter(Coords *);
double circleArea(Coords *);
double triangleArea(Coords *, double);