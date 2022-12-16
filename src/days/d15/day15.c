//
// Created by Ilyes on 15/12/2022.
//

#include "../../Common.h"

struct line
{
    int segments[40*2], segment_nb;
    int dead_indexes[40], dead_indexes_nb;
    int value;
};

void init_line(struct line* line)
{
    line->segment_nb = 0;
    line->dead_indexes_nb = 0;
    line->value = 0;
}

void insert_segment(int min_x, int max_x, struct line* line)
{
    bool is_contained = false;
    for (int i = 0; i < line->segment_nb * 2; i += 2)
    {
        bool index_is_dead = false;
        for (int j = 0; j < line->dead_indexes_nb; index_is_dead = index_is_dead || i == line->dead_indexes[j], j++);
        if (index_is_dead)
            continue;

        if (min_x >= line->segments[i] && max_x <= line->segments[i + 1])
        {
            is_contained = true;
            break;
        }
        else if (min_x >= line->segments[i] && min_x <= line->segments[i + 1])
            min_x = line->segments[i + 1] + 1;
        else if (max_x >= line->segments[i] && max_x <= line->segments[i + 1])
            max_x = line->segments[i] - 1;
        else if (min_x <= line->segments[i] && max_x >= line->segments[i + 1])
        {
            line->value -= (line->segments[i + 1] - line->segments[i] + 1);
            line->dead_indexes[line->dead_indexes_nb] = i;
            line->dead_indexes_nb++;
        }
    }
    if (!is_contained)
    {
        line->segments[line->segment_nb * 2] = min_x;
        line->segments[line->segment_nb * 2 + 1] = max_x;
        line->segment_nb++;
        line->value += max_x - min_x + 1;
    }
}

bool is_line_complete(struct line* line)
{
    int current_value = line->value;
    insert_segment(0, 4000000, line);
    if (current_value != line->value)
        return true;
    return false;
}

void day15(enum Part part)
{
    clock_t begin = clock();

    FILE* input = fopen("../src/days/d15/input.txt", "r");
    char line[100];

    struct line line_2millions;
    init_line(&line_2millions);

    struct line* map;
    if (part == PART2)
        map = malloc(sizeof(struct line) * 4000001);

    if (part == PART2)
    {
        for (int i = 0; i <= 4000000; i++)
            init_line(map + i);
    }

    while(fgets(line, 100, input))
    {
        char* iterator = line;
        int sensor_x = strtol(iterator + 12, &iterator, 10);
        int sensor_y = strtol(iterator + 4, &iterator, 10);
        int beacon_x = strtol(iterator + 25, &iterator, 10);
        int beacon_y = strtol(iterator + 4, NULL, 10);
        int radius = abs(sensor_x - beacon_x) + abs(sensor_y - beacon_y);

        if (part == PART1)
        {
            int dist_to_2m = abs(sensor_y - 2000000);
            if (beacon_y == 2000000)
            {
                bool is_found = false;
                for (int i = 0; i < line_2millions.segment_nb * 2; i += 2, is_found = is_found || (line_2millions.segments[i] == beacon_x));
                if (!is_found)
                {
                    line_2millions.segments[line_2millions.segment_nb * 2] = beacon_x;
                    line_2millions.segments[line_2millions.segment_nb * 2 + 1] = beacon_x;
                    line_2millions.segment_nb++;
                }
            }
            if (dist_to_2m <= radius)
            {
                int min_x = sensor_x - radius + dist_to_2m;
                int max_x = sensor_x + radius - dist_to_2m;
                insert_segment(min_x, max_x, &line_2millions);
            }
        }
        else if (part == PART2)
        {
            for (int i = 0; i <= 4000000; i++)
            {
                int dist_to_targeted_y = abs(sensor_y - i);
                if (dist_to_targeted_y <= radius)
                {
                    int min_x = sensor_x - radius + dist_to_targeted_y;
                    int max_x = sensor_x + radius - dist_to_targeted_y;
                    insert_segment(min_x, max_x, map + i);
                }
            }
        }
    }

    int64_t output = line_2millions.value;

    if (part == PART2)
    {
        for (int64_t i = 0; i <= 4000000; i++)
        {
            if (is_line_complete(map + i))
            {
                int64_t j = 0;
                int64_t current_j;
                do
                {
                    current_j = j;
                    for (int k = 0; k < (map[i].segment_nb - 1)*2; k+=2)
                    {
                        if ((int64_t)(map[i].segments[k]) <= j && (int64_t)(map[i].segments[k+1]) >= j)
                            j = map[i].segments[k+1] + 1;
                    }
                } while (current_j != j);

                output = j * 4000000 + i;
                break;
            }
        }
    }

    clock_t end = clock();

    printf("%llu\n", output);
    printf("Done in %f ms\n", (double)(end - begin) / (double)CLOCKS_PER_SEC * 1000.);

    fclose(input);
    if (part == PART2)
        free(map);
}