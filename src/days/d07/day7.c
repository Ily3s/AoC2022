//
// Created by Ilyes on 07/12/2022.
//

#include "../../Common.h"

void day7(enum Part part)
{
    FILE* input = fopen("../src/days/d07/input.txt", "r");

    char line[50];
    uint64_t* done_dir_sizes = malloc(64);
    uint64_t* undone_dir_sizes = malloc(64);
    int done_capacity = 8, undone_capacity = 8;
    int done_size = 0, undone_size = 0;

    while(fgets(line, 50, input))
    {
        if (line[0] == '$' && line[2] == 'c')
        {
            if (line[5] != '.')
            {
                if (undone_size == undone_capacity)
                {
                    undone_capacity += 4;
                    undone_dir_sizes = realloc(undone_dir_sizes, undone_capacity * 8);
                }
                undone_dir_sizes[undone_size] = 0;
                undone_size++;
            }
            else
            {
                if (done_size == done_capacity)
                {
                    done_capacity += 4;
                    done_dir_sizes = realloc(done_dir_sizes, done_capacity * 8);
                }
                done_dir_sizes[done_size] = undone_dir_sizes[undone_size - 1];
                undone_size--;
                done_size++;
            }
        }
        if (line[0] != '$' && line[0] <= 57)
        {
            uint64_t size_of_file = 0;
            for (int i = 0; i < strlen(line) && line[i] != ' '; i++)
                size_of_file = size_of_file * 10 + line[i] - 48;

            for (int i = 0; i < undone_size; i++)
                undone_dir_sizes[i] += size_of_file;
        }
    }

    for (int i = 0; i < undone_size;)
    {
        if (done_size == done_capacity)
        {
            done_capacity += 4;
            done_dir_sizes = realloc(done_dir_sizes, done_capacity * 8);
        }
        done_dir_sizes[done_size] = undone_dir_sizes[undone_size - 1];
        undone_size--;
        done_size++;
    }

    uint64_t output = 0;

    if (part == PART1)
    {
        for (int i = 0; i < done_size; i++)
        {
            if (done_dir_sizes[i] <= 100000)
                output += done_dir_sizes[i];
        }
    }
    else if (part == PART2)
    {
        output = UINT64_MAX;
        for (int i = 0; i < done_size; i++)
        {
            if (done_dir_sizes[i] >= 30000000 - (70000000 - undone_dir_sizes[0]) && done_dir_sizes[i] < output)
                output = done_dir_sizes[i];
        }
    }

    printf("%llu\n", output);

    fclose(input);
}