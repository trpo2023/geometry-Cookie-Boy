#ifndef HANDLER_H
#define HANDLER_H
#define MAX_ELEMENTS 255
#define MIN_ELEMENTS 10
#define CIRCLE_START 6
#define TRIANGLE_START 8

typedef struct {
    int figureType;
    char name[MAX_ELEMENTS];
    double coords[MIN_ELEMENTS];
    int intersects[MIN_ELEMENTS];
} Figure;

void skipSpaces(char*, Figure*, int*);
void fillErrorString(char*, int, char*);
double getValue(char*, int*, Figure*, char, char*);
int circleHandler(char*, Figure*, char*);
int triangleHandler(char*, Figure*, char*);
int stringHandler(char*, Figure*, char*);

#endif
