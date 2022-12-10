//
// Created by Ilyes on 09/12/2022.
//

#include "../../Common.h"

struct Position
{
    int x, y;
};

void day9(enum Part part)
{
    FILE* input = fopen("../src/days/d09/input.txt", "r");
    char line[10];

    int rope_size = 0;
    if (part == PART1)
        rope_size = 2;
    else if (part == PART2)
        rope_size = 10;

    struct Position rope[10];
    for (int i = 0; i < 10; i++)
    {
        rope[i].x = 0;
        rope[i].y = 0;
    }

    struct Position* positions = malloc(100000);
    int pos_index = 1;
    positions[0].x = 0; positions[0].y = 0;

    while (fgets(line, 10, input))
    {
        int nb_of_steps = atoi(line + 2);

        for (int i = 0; i < nb_of_steps; i++)
        {
            rope[0].x += (line[0] == 'R') - (line[0] == 'L');
            rope[0].y += (line[0] == 'U') - (line[0] == 'D');

            for (int knot_i = 0; knot_i < rope_size - 1; knot_i++)
            {
                if (abs(rope[knot_i].x - rope[knot_i + 1].x) > 1 && rope[knot_i].y != rope[knot_i + 1].y)
                    rope[knot_i + 1].y += 2*(rope[knot_i].y > rope[knot_i + 1].y) - 1;

                if (abs(rope[knot_i].y - rope[knot_i + 1].y) > 1 && rope[knot_i].x != rope[knot_i + 1].x)
                    rope[knot_i + 1].x = rope[knot_i].x;

                rope[knot_i + 1].x += (rope[knot_i].x - rope[knot_i + 1].x) / 2;
                rope[knot_i + 1].y += (rope[knot_i].y - rope[knot_i + 1].y) / 2;
            }

            bool not_found = true;
            for (int j = 0; j < pos_index; j++)
            {
                not_found = not_found && (positions[j].x != rope[rope_size - 1].x || positions[j].y != rope[rope_size - 1].y);
            }
            if (not_found)
            {
                positions[pos_index].x = rope[rope_size - 1].x;
                positions[pos_index].y = rope[rope_size - 1].y;
                pos_index++;
            }
        }
    }

    printf("%d\n", pos_index);

    fclose(input);
}