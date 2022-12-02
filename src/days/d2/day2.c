//
// Created by Ilyes on 02/12/2022.
//

#include "../../Common.h"

void day2(enum Part part)
{
    FILE* file = fopen("../src/days/d2/input.txt", "r");

    char line[5];
    uint64_t total_score = 0;

    while (fgets(line, 5, file))
    {
        if (part == PART1)
        {
            total_score += line[2] - 87;
            if ((line[2] - line[0]) == 23)
                total_score += 3;
            else if ((line[2] == 'X' && line[0] == 'C')
                     || (line[2] == 'Y' && line[0] == 'A')
                     || (line[2] == 'Z' && line[0] == 'B')) {
                total_score += 6;
            }
        }
        else if (part == PART2)
        {
            total_score += 3 * (line[2] - 88);
            total_score += (((line[0] - 65) + ((line[2] - 86)%3))%3) + 1;
        }
    }

    printf("%llu\n", total_score);

    fclose(file);
}