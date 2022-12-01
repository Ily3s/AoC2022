//
// Created by Ilyes on 01/12/2022.
//

#include "../../Common.h"

void day1(enum Part part)
{
    FILE* file = fopen("../src/days/d1/input.txt", "rb");

    int max1 = 0, max2 = 0, max3 = 0;
    int current = 0;

    char line[10];
    while (fgets(line, 10, file))
    {
        if (line[0] == '\n' || line[0] == '\r')
        {
            if (current > max1)
            {
                max3 = max2;
                max2 = max1;
                max1 = current;
            }
            else if (current > max2)
            {
                max3 = max2;
                max2 = current;
            }
            else if (current > max3)
                max3 = current;

            current = 0;
        }
        else
            current += atoi(line);
    }

    if (part == PART1)
        printf("%d\n", max1);
    else if (part == PART2)
        printf("%d\n", max1+max2+max3);

    fclose(file);
}