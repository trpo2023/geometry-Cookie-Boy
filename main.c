#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct figure {
    char name[255];
    double coords[10];
    double radius;
    double perimeter;
    double area;
    int intersects[10];
};

void space(int n, char* string)
{
    printf("%s", string);
    for (int i = 0; i < n; i++)
        printf(" ");
}

int skipSpaces(char* string, int n)
{
    while (string[n] == ' ')
        n++;
    return n;
}

int wordHandler(char* string)
{
    char* tempStr = (char*)malloc(sizeof(char) * strlen(string));

    for (int i = 0; i < strlen(string); i++) {
        tempStr[i] = '\0'; // Для strcmp
        if (!strcmp(tempStr,
                    "circle")) // strcmp в случае совпадения возвращает 0
        {
            if (string[i] != '(') {
                space(i, string);
                printf("^\nError at column %d: expected '('", i);
                return 0;
            }
            free(tempStr);
            return 1;
        } else {
            string[i] = tolower(string[i]); // Преобразуем в нижний регистр
            tempStr[i] = string[i];
        }
    }
    space(0, string);
    printf("^\nError at column %d: expected 'circle'", 0);
    free(tempStr);
    return 0;
}

int takeElement(char* string, char* axis, char ch, int n)
{
    int i = n, j = 0;

    while (string[i] != ch) {
        if (((string[i] >= '0') && (string[i] <= '9')) || (string[i] == '.')) {
            axis[j] = string[i];
            j++;
        } else {
            axis[j] = '\0';
            if ((strlen(axis) > 0) && (axis[j - 1] != '.')) {
                space(i, string);
                printf("^\nError at column %d: expected '%c'", i, ch);
                return 0;
            }
            space(i, string);
            printf("^\nError at column %d: expected '<double>'", i);
            return 0;
        }
        i++;
    }

    axis[j] = '\0';
    i++;
    return i;
}

int circleHandler(char* string, struct figure structure)
{
    char* elements = " ,)";
    char axis[10];
    int i = 7; // т.к. "circle("
    int j = 0;

    for (int el = 0; el < strlen(elements); el++) {
        i = skipSpaces(string, i);
        int head = i;
        i = takeElement(string, axis, elements[el], i);
        if (i != 0) {
            double value = atof(axis); // atof возвращает фигню, надо исправить!
            if ((value != 0) || (!strcmp(axis, "0"))
                || (!strcmp(axis, "0.0"))) {
                structure.coords[j] = value;
                j++;
                axis[0] = '\0';
            } else {
                space(head, string);
                printf("^\nError at column %d: expected '<double>'", head);
                return 0;
            }
        } else {
            return 0;
        }
    }
    return i;
}

void fillString(char* string, char* name)
{
    int i;
    for (i = 0; i < strlen(string); i++) {
        name[i] = string[i];
    }
    name[i] = '\0';
}

int main(int argc, char* argv[])
{
    if (argv[1] == NULL) {
        printf("The input is a file with format lines: circle(point, "
               "number)\n");
        return 0;
    }
    FILE* file = fopen(argv[1], "r");
    char line[255];
    struct figure structure[10];
    int j = 0;

    // for (int i = 0; !feof(file); i++)
    while (fgets(line, 255, file) != 0) {
        if (line[strlen(line) - 1] != '\n') // Для последней строки
        {
            int length = strlen(line);
            line[length] = '\n';
            line[length + 1] = '\0';
        }
        if (wordHandler(line) == 1) {
            int index = circleHandler(line, structure[j]);
            if (index != 0) {
                fillString(line, structure[j].name);
                j++;
            } else {
                return 1;
            }
        } else {
            return 1;
        }
    }

    for (int el = 0; el < j; el++) {
        printf("%d. %s", el + 1, structure[el].name);
    }

    return 0;
}
