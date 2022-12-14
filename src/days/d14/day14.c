//
// Created by Ilyes on 14/12/2022.
//

#include "../../Common.h"

uint8_t map[1000][200];

void day14(enum Part part)
{
    FILE* input = fopen("../src/days/d14/input.txt", "r");

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 200; j++)
            map[i][j] = 0;
    }

    char line[300];

    int max_height = 0;

    while (fgets(line, 300, input))
    {
        char* ptr = line;

        while (true)
        {
            char *coma, *arrow, *end;
            int x1 = strtol(ptr, &coma, 10);
            int y1 = strtol(coma + 1, &arrow, 10);

            int x2 = strtol(arrow + 3, &coma, 10);
            int y2 = strtol(coma + 1, &end, 10);

            max_height = max(max_height, max(y1, y2));

            if (x1 == x2)
            {
                for (int j = y1; j != y2; j += 1 - 2*(y1 > y2))
                    map[x1][j] = 1;
                map[x1][y2] = 1;
            }
            else if (y1 == y2)
            {
                for (int i = x1; i != x2; i += 1 - 2*(x1 > x2))
                    map[i][y1] = 1;
                map[x2][y1] = 1;
            }

            if (end >= line + strlen(line) || *end == '\n' || *end == '\r')
                break;

            ptr = arrow + 3;
        }
    }

    if (part == PART2)
    {
        max_height += 2;
        for (int i = 0; i < 1000; i++)
            map[i][max_height] = 1;
    }

    bool end_reached = false;
    int output = -2 + part;

    for (;!end_reached && !map[500][0]; output++)
    {
        for (int x = 500, y = 0;; y++)
        {
            if (y > max_height)
            {
                end_reached = true;
                break;
            }

            if (map[x][y+1])
            {
                if (map[x-1][y+1])
                {
                    if (map[x+1][y+1])
                    {
                        map[x][y] = 1;
                        break;
                    }
                    else
                        x++;
                }
                else
                    x--;
            }
        }
    }

    printf("%d\n", output);

    fclose(input);
}