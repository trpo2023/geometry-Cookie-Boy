#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        return 1;
    }

    Figure figures[MIN_ELEMENTS];
    char line[MAX_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    errmsg[0] = '\0';
    int j = 0;

    while (fgets(line, MAX_ELEMENTS, file))
    {
        if (line[strlen(line) - 1] != '\n') // Для последней строки
        {
            int length = strlen(line);
            line[length] = '\n';
            line[length + 1] = '\0';
        }

        stringHandler(line, &figures[j], errmsg);

        if (strlen(errmsg) != 0)
            break;

        j++;
    }

    if (strlen(errmsg) == 0)
    {
        for (int i = 0; i < j; i++)
        {
            int el = 0;
            printf("%d. %s\n", i + 1, figures[i].name);
            double perimeter;
            if (!strcmp(figures[i].type, "circle"))
            {
                perimeter = circlePerimeter(figures[i].coords);
                printf("\tperimeter = %.3lf\n", perimeter);
                printf("\tarea = %.3lf\n", circleArea(figures[i].coords));
                printf("\tintersects:\n");
                if (getIntersections(figures, i, j))
                {
                    while (figures[i].intersects[el])
                    {
                        printf("\t  %d. %s\n", figures[i].intersects[el], figures[figures[i].intersects[el] - 1].type);
                        el++;
                    }
                }
                else
                {
                    printf("\t  None\n");
                }
            }
            else if (!strcmp(figures[i].type, "triangle"))
            {
                perimeter = trianglePerimeter(figures[i].coords);
                printf("\tperimeter = %.3lf\n", perimeter);
                printf("\tarea = %.3lf\n", triangleArea(figures[i].coords, perimeter / 2));
                printf("\tintersects:\n");
                if (getIntersections(figures, i, j))
                {
                    while (figures[i].intersects[el])
                    {
                        printf("\t  %d. %s\n", figures[i].intersects[el], figures[figures[i].intersects[el] - 1].type);
                        el++;
                    }
                }
                else
                {
                    printf("\t  None\n");
                }
            }
            printf("\n");
        }
    }
    else
    {
        char temp[MIN_ELEMENTS];
        sprintf(temp, "%d", j + 1);
        printf("%d. %s", j + 1, line);
        addSpaces(strlen(temp) + 2);
        printf("%s", errmsg);
        return 1;
    }

    return 0;
}
