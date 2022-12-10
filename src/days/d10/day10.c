//
// Created by Ilyes on 10/12/2022.
//

#include "../../Common.h"

int clock = 0, X = 1, output = 0, next_cap = 19;

void draw_pixel()
{
    if ((clock % 40) == 0)
        printf("\n");
    printf("%c", 32 + 3*((int)(abs(X - (clock % 40))) <= 1));
}

void day10(enum Part part)
{
    FILE* input = fopen("../src/days/d10/input.txt", "r");
    char line[20];

    while(fgets(line, 20, input))
    {
        if (clock >= next_cap)
        {
            output += (next_cap + 1) * X;
            next_cap += 40;
        }
        if (line[0] == 'n')
        {
            if (part == PART2)
                draw_pixel();
            clock++;
        }
        else if (line[0] == 'a')
        {
            for (int i = 0; i < 2; i++)
            {
                if (part == PART2)
                    draw_pixel();
                clock++;
            }
            if (clock > next_cap)
            {
                output += (next_cap + 1) * X;
                next_cap += 40;
            }
            X += atoi(line + 5);
        }
    }

    if (part == PART1)
        printf("%d\n", output);
    else if (part == PART2)
        printf("\n\n");

    fclose(input);
}