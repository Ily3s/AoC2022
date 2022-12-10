//
// Created by Ilyes on 04/12/2022.
//

#include "../../Common.h"

void day4(enum Part part)
{
    FILE* input = fopen("../src/days/d04/input.txt", "r");
    int output = 0;
    char line[20];
    while (fgets(line, 20, input))
    {
        int bounds[4] = {0, 0, 0, 0};
        int index = 0;
        for (int i = 0; i < 4; i++)
        {
            for (; line[index] != '-' && line[index] != ',' && line[index] != '\n' && line[index] != '\r' && index < strlen(line); index++)
            {
                bounds[i] *= 10;
                bounds[i] += (line[index] - 48);
            }
            index++;
        }

        if (part == PART1)
            output += ( (bounds[0] <= bounds[2] && bounds[1] >= bounds[3]) || (bounds[0] >= bounds[2] && bounds[1] <= bounds[3]) );
        else if (part == PART2)
            output += ( (bounds[1] <= bounds[3] && bounds[1] >= bounds[2]) || (bounds[0] >= bounds[2] && bounds[0] <= bounds[3]) || (bounds[0] <= bounds[2] && bounds[1] >= bounds[3]) );

    }

    printf("%d\n", output);
    fclose(input);
}