#include <stdio.h>
#include <string.h>

#include <calculations.h>
#include <intersections.h>
#include <handler.h>

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        printf("The input is a file with format lines: 'circle(point, number)' "
               "or 'triangle((point, point, point, point))'\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error! Failed to open file!\n");
        fclose(file);
        return 1;
    }

    Figure figures[MIN_ELEMENTS];
    char line[MAX_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    errmsg[0] = '\0';
    int count = 0;

    while (fgets(line, MAX_ELEMENTS, file))
    {
        if (line[strlen(line) - 1] != '\n') // Для последней строки
        {
            int length = strlen(line);
            line[length] = '\n';
            line[length + 1] = '\0';
        }
        stringHandler(line, &figures[count], errmsg);
        if (strlen(errmsg))
        {
            char temp[MIN_ELEMENTS];
            sprintf(temp, "%d", count + 1);
            printf("%d. %s", count + 1, line);
            addSpaces(strlen(temp) + 2);
            printf("%s\n", errmsg);
            return 1;
        }
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s\n", i + 1, figures[i].name);
        if (!strcmp(figures[i].type, "circle"))
        {
            printf("\tperimeter = %.3lf\n", circlePerimeter(figures[i].coords));
            printf("\tarea = %.3lf\n", circleArea(figures[i].coords));
            printf("\tintersects:\n"); printIntersections(figures, i, count);
        }
        else if (!strcmp(figures[i].type, "triangle"))
        {
            double perimeter = trianglePerimeter(figures[i].coords);
            printf("\tperimeter = %.3lf\n", perimeter);
            printf("\tarea = %.3lf\n", triangleArea(figures[i].coords, perimeter / 2));
            printf("\tintersects:\n"); printIntersections(figures, i, count);
        }
        printf("\n");
    }

    return 0;
}
