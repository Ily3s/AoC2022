//
// Created by Ilyes on 11/12/2022.
//

#include "../../Common.h"

struct Monkey
{
    int nb_of_inspections;
    int addition, multiplication;
    bool squaring;
    int items[100];
    int indices[100], indices_size;
    int divisibility;
    int if_true, if_false;
};

void day11(enum Part part)
{
    FILE* input = fopen("../src/days/d11/input.txt", "r");

    struct Monkey monkeys[10];
    int monkeys_nb = 0, items_nb = 0;

    char line[100];

    for (int i = 0; i < 10; i++)
    {
        monkeys[i].nb_of_inspections = 0;
        monkeys[i].addition = 0;
        monkeys[i].multiplication = 1;
        monkeys[i].squaring = false;
        monkeys[i].indices_size = 0;
        for (int j = 0; j < 100; j++)
            monkeys[i].items[j] = 0;
    }

    while(fgets(line, 100, input))
    {
        if (line[0] == '\n' || line[0] == '\r')
            monkeys_nb++;
        else if (line[2] == 'S')
        {

            for (int i = 18; i < strlen(line) && line[i] != '\n' && line[i] != '\r'; i++)
            {
                if (line[i] == ',')
                {
                    monkeys[monkeys_nb].indices[monkeys[monkeys_nb].indices_size] = items_nb;
                    monkeys[monkeys_nb].indices_size++;
                    items_nb++;
                    i++;
                    continue;
                }
                for (int j = 0; j < 10; j++)
                {
                    monkeys[j].items[items_nb] *= 10;
                    monkeys[j].items[items_nb] += line[i] - 48;
                }
            }
            monkeys[monkeys_nb].indices[monkeys[monkeys_nb].indices_size] = items_nb;
            monkeys[monkeys_nb].indices_size++;
            items_nb++;
        }
        else if (line[2] == 'O')
        {
            if (line[23] == '*' && line[25] == 'o')
                monkeys[monkeys_nb].squaring = true;
            else if (line[23] == '*')
                monkeys[monkeys_nb].multiplication = atoi(line + 25);
            else if (line[23] == '+')
                monkeys[monkeys_nb].addition = atoi(line + 25);
        }
        else if (line[2] == 'T')
            monkeys[monkeys_nb].divisibility = atoi(line + 21);
        else if (line[7] == 't')
            monkeys[monkeys_nb].if_true = atoi(line + 29);
        else if (line[7] == 'f')
            monkeys[monkeys_nb].if_false = atoi(line + 29);
    }

    monkeys_nb++;

    for (int i = 0; i < 20 + 9980*(part == PART2) ; i++)
    {
        for (int j = 0; j < monkeys_nb; j++)
        {
            for (int k = 0; k < monkeys[j].indices_size; k++)
            {
                for (int iranoutofletters = 0; iranoutofletters < monkeys_nb; iranoutofletters++)
                    monkeys[iranoutofletters].items[monkeys[j].indices[k]] = (((monkeys[iranoutofletters].items[monkeys[j].indices[k]] + monkeys[j].addition) * monkeys[j].multiplication) * (1 + monkeys[j].squaring*(monkeys[iranoutofletters].items[monkeys[j].indices[k]]-1))) / (1 + 2*(part == PART1)) % ((part == PART1)*999999999 + monkeys[iranoutofletters].divisibility); // Longest line of code I've ever written in my entire life
                int throw_to = (monkeys[j].items[monkeys[j].indices[k]] % monkeys[j].divisibility == 0) * monkeys[j].if_true + (monkeys[j].items[monkeys[j].indices[k]] % monkeys[j].divisibility != 0) * monkeys[j].if_false;
                monkeys[throw_to].indices[monkeys[throw_to].indices_size] = monkeys[j].indices[k];
                monkeys[throw_to].indices_size++;
                monkeys[j].nb_of_inspections++;
            }
            monkeys[j].indices_size = 0;
        }
    }

    int first = 0, second = 0;

    for (int i = 0; i < monkeys_nb; i++)
    {
        if (monkeys[i].nb_of_inspections >= first)
        {
            second = first;
            first = monkeys[i].nb_of_inspections;
        }
        else if (monkeys[i].nb_of_inspections >= second)
            second = monkeys[i].nb_of_inspections;
    }

    printf("%llu\n", (unsigned long long) first*second);

    fclose(input);
}
