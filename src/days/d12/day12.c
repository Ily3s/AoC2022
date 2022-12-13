//
// Created by Ilyes on 12/12/2022.
//

#include "../../Common.h"

struct pos
{
    int x, y;
};

void day12(enum Part part)
{
    clock_t start_time = clock();

    FILE* input = fopen("../src/days/d12/input.txt", "r");

    char line[200];

    struct pos* checked_pos = malloc(4 * 2 * 200 * 50);
    struct pos starting = {0, 0}, ending = {0, 0};
    char** map = malloc(50 * sizeof (char*));
    int lines_nb = 0;
    int length = 0;
    int size = 1;

    for (; fgets(line, 200, input); lines_nb++)
    {
        length = strlen(line);
        if (line[strlen(line) - 2] == '\r')
        {
            line[strlen(line) - 2] = 0;
            length--;
        }
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = 0;
            length--;
        }
        map[lines_nb] = malloc(length);
        strcpy(map[lines_nb], line);
        for (int i = 0; i < length; i++)
        {
            starting.x += i*(line[i] == 'S');
            starting.y += lines_nb*(line[i] == 'S');

            ending.x += i*(line[i] == 'E');
            ending.y += lines_nb*(line[i] == 'E');

            if (part == PART2 && line[i] == 'a')
            {
                checked_pos[size].x = i;
                checked_pos[size].y = lines_nb;
                size++;
            }
        }
    }

    map[starting.y][starting.x] = 'a';
    map[ending.y][ending.x] = 'z';

    checked_pos[0] = starting;
    int index = 0;
    uint64_t path_length = 0;

    bool stop = false;

    for (;!stop; path_length++)
    {
        int current_size = size;
        for (int i = index; i < current_size; i++)
        {
            struct pos valid_moves[4] =
                    {
                    {checked_pos[i].x - 1, checked_pos[i].y},
                    {checked_pos[i].x + 1, checked_pos[i].y},
                    {checked_pos[i].x, checked_pos[i].y - 1},
                    {checked_pos[i].x, checked_pos[i].y + 1}
                    };

            for (int j = 0; j < 4; j++)
            {
                bool is_valid = valid_moves[j].x >= 0 && valid_moves[j].x < length && valid_moves[j].y >= 0 && valid_moves[j].y < lines_nb;
                is_valid = is_valid && (map[valid_moves[j].y][valid_moves[j].x] - map[checked_pos[i].y][checked_pos[i].x] <= 1);
                if (is_valid)
                {
                    for (int k = 0; k < size; k++)
                        is_valid = is_valid && !(checked_pos[k].x == valid_moves[j].x && checked_pos[k].y == valid_moves[j].y);
                }

                if (is_valid)
                {
                    checked_pos[size] = valid_moves[j];
                    size++;
                    if (valid_moves[j].x == ending.x && valid_moves[j].y == ending.y)
                    {
                        stop = true;
                        break;
                    }
                }
            }
            if (stop)
                break;
        }
        index = current_size;
    }

    double duration = (double)(clock() - start_time) / (double)CLOCKS_PER_SEC;

    printf("%llu\n", path_length);

    fclose(input);

    printf("Done in %f ms\n", duration * 1000);
}