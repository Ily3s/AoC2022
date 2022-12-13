//
// Created by Ilyes on 13/12/2022.
//

#include "../../Common.h"

int compare(char* first, int sizeof_first, char* second, int sizeof_second);
int compare_lists(char* first, int sizeof_first, char* second, int sizeof_second);

void day13(enum Part part)
{
    FILE* input = fopen("../src/days/d13/input.txt", "r");

    char line1[300], line2[300], blank_line[5];
    char divider1[] = "[[2]]", divider2[] = "[[6]]";
    int divider1_index = 1, divider2_index = 2;

    int output = 0;

    for (int i = 1; fgets(line1, 300, input) && fgets(line2, 300, input); i++)
    {
        fgets(blank_line, 5, input);

        line1[strlen(line1) - 1] = 0;
        if (line1[strlen(line1) - 2] == '\r')
            line1[strlen(line1) - 2] = 0;
        line2[strlen(line2) - 1] = 0;
        if (line2[strlen(line2) - 2] == '\r')
            line2[strlen(line2) - 2] = 0;

        if (part == PART1)
            output += i * compare(line1, strlen(line1), line2, strlen(line2));
        else if (part == PART2)
        {
            divider1_index += (compare(line1, strlen(line1), divider1, 5));
            divider1_index += (compare(line2, strlen(line2), divider1, 5));

            divider2_index += (compare(line1, strlen(line1), divider2, 5));
            divider2_index += (compare(line2, strlen(line2), divider2, 5));
        }
    }

    if (part == PART2)
        output = divider1_index * divider2_index;

    printf("%d\n", output);

    fclose(input);
}

int compare(char* first, int sizeof_first, char* second, int sizeof_second)
{
    if (!sizeof_first && sizeof_second)
        return true;
    else if (sizeof_first && !sizeof_second)
        return false;

    if (first[0] != '[' && second[0] != '[')
    {
        if (atoi(first) < atoi(second))
            return true;
        else if (atoi(first) > atoi(second))
            return false;
        return -1;
    }
    else if (first[0] == '[' && second[0] == '[')
    {
        return compare_lists(first, sizeof_first, second, sizeof_second);
    }
    else if (first[0] != '[')
    {
        char* new_first = malloc(sizeof_first + 2);
        new_first[sizeof_first + 1] = ']';
        new_first[0] = '[';
        memcpy(new_first + 1, first, sizeof_first);
        int out = compare_lists(new_first, sizeof_first + 2, second, sizeof_second);
        free(new_first);
        return out;
    }
    else
    {
        char* new_second = malloc(sizeof_second + 2);
        new_second[sizeof_second + 1] = ']';
        new_second[0] = '[';
        memcpy(new_second + 1, second, sizeof_second);
        int out = compare_lists(first, sizeof_first, new_second, sizeof_second + 2);
        free(new_second);
        return out;
    }
}

int compare_lists(char* first, int sizeof_first, char* second, int sizeof_second)
{
    int fst_index = 1, snd_index = 1;
    int enclosing1 = 1, enclosing2 = 1;

    while (true)
    {
        int fst_index_cpy = fst_index, snd_index_cpy = snd_index;

        for (; fst_index < sizeof_first; fst_index++)
        {
            enclosing1 += (first[fst_index] == '[') - (first[fst_index] == ']');
            if (enclosing1 == 1 && first[fst_index] == ',')
                break;
            if (!enclosing1)
                break;
        }
        fst_index++;
        bool ran_out1 = fst_index == sizeof_first;

        for (; snd_index < sizeof_second; snd_index++)
        {
            enclosing2 += (second[snd_index] == '[') - (second[snd_index] == ']');
            if (enclosing2 == 1 && second[snd_index] == ',')
                break;
            if (!enclosing2)
                break;
        }
        snd_index++;
        bool ran_out2 = snd_index == sizeof_second;

        int c = compare(first + fst_index_cpy, fst_index - fst_index_cpy - 1, second + snd_index_cpy,
                        snd_index - snd_index_cpy - 1);

        if (c != -1)
            return c;

        if (ran_out1 && !ran_out2)
            return true;
        else if (ran_out2 && !ran_out1)
            return false;
        else if (ran_out1 && ran_out2)
            return -1;
    }
}