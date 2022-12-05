//
// Created by Ilyes on 05/12/2022.
//

#include "../../Common.h"

struct Stack
{
    uint64_t capacity, size;
    char* buffer;
};

void init_stack(struct Stack* stack)
{
    stack->capacity = 0;
    stack->size = 0;
    stack->buffer = NULL;
}

void realloc_stack(struct Stack* stack)
{
    stack->capacity = (stack->capacity + 2) * 2;
    char* new_buffer = malloc(stack->capacity);
    for (uint64_t i = 0; i < stack->size; i++)
        new_buffer[i] = stack->buffer[i];
    if (stack->buffer != NULL)
        free(stack->buffer);
    stack->buffer = new_buffer;
}

void push(struct Stack* stack, char c)
{
    if (stack->size >= stack->capacity)
        realloc_stack(stack);
    stack->buffer[stack->size] = c;
    stack->size++;
}

void pop(struct Stack* stack)
{
    stack->size--;
}

char back(const struct Stack* stack)
{
    return stack->buffer[stack->size-1];
}

void free_stack(struct Stack* stack)
{
    stack->capacity = 0;
    stack->size = 0;
    if (stack->buffer != NULL)
        free(stack->buffer);
}

void day5(enum Part part)
{
    FILE* input = fopen("../src/days/d5/input.txt", "r");
    char output[21];

    struct Stack stacks[20];
    int stacks_nb = 0;
    for (int i = 0; i < 20; i++)
        init_stack(&stacks[i]);

    char lines[20][100];
    int end_of_stacks = 0;
    for (; fgets(lines[end_of_stacks], 100, input) && lines[end_of_stacks][1] != '1'; end_of_stacks++);

    stacks_nb = (lines[end_of_stacks][strlen(lines[end_of_stacks]) - 2 - (lines[end_of_stacks][strlen(lines[end_of_stacks]) -2] == '\r')]) - 48;

    for (int i = end_of_stacks - 1; i >= 0; i--)
    {
        for (int j = 0; j < strlen(lines[i]); j++)
        {
            if (lines[i][j] == '[')
                push(&stacks[j/4], lines[i][j+1]);
        }
    }

    char line[100];
    fgets(line, 100, input);
    while (fgets(line, 100, input))
    {
        int numbers[3] = {0, 0, 0};
        int index = 5;
        for (int i = 0; i < 5; i++)
        {
            for(; line[index] != ' ' && line[index] != '\r' && line[index] != '\n' && index < strlen(line); index++)
            {
                if (i % 2 == 0)
                {
                    numbers[i/2] *= 10;
                    numbers[i/2] += line[index] - 48;
                }
            }
            index++;
        }

        if (part == PART1)
        {
            for (int i = 0; i < numbers[0]; i++)
            {
                push(&stacks[numbers[2] - 1], back(&stacks[numbers[1] - 1]));
                pop(&stacks[numbers[1] - 1]);
            }
        }
        else if (part == PART2)
        {
            for (int i = numbers[0]; i > 0; i--)
                push(&stacks[numbers[2] - 1], stacks[numbers[1] - 1].buffer[stacks[numbers[1] - 1].size - i]);
            for (int i = 0; i < numbers[0]; i++)
                pop(&stacks[numbers[1] - 1]);
        }
    }

    int ind = 0;
    for (; ind < stacks_nb; ind++)
        output[ind] = back(&stacks[ind]);
    output[ind] = 0;

    printf("%s\n", output);

    for (int i = 0; i < stacks_nb; i++)
        free_stack(&stacks[i]);

    fclose(input);
}