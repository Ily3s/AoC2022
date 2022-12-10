//
// Created by Ilyes on 06/12/2022.
//

#include "../../Common.h"

void day6(enum Part part)
{
    FILE* input = fopen("../src/days/d06/input.txt", "r");
    char buffer[14];
    char current[2];
    int i = 1;
    for (; fgets(current, 2, input); i++)
    {
        for (int index = 13; index > 0; index--)
            buffer[index] = buffer[index - 1];
        buffer[0] = current[0];

        int size_of_buffer = (4 + 10*(part == PART2));

        if (i >= size_of_buffer)
        {
            bool is_marker = true;
            for (int a = 0; a < size_of_buffer - 1; a++)
            {
                for (int b = a+1; b < size_of_buffer; b++)
                    is_marker = is_marker && (buffer[a] != buffer[b]);
            }
            if (is_marker)
                break;
        }
    }
    printf("%d\n", i);
}