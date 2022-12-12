#include "Common.h"

int main()
{
    bool should_end = false;

    while (!should_end)
    {
        printf("Type <day> <part> or \"quit\"/\"exit\"/\"stop\"\n>");
        char line[10];
        fgets(line, 10, stdin);
        if (!strcmp(line, "quit\n") || !strcmp(line, "exit\n") || !strcmp(line, "stop\n"))
        {
            should_end = true;
        }
        else
        {
            int day_nb = 0, part_nb = 0;

            int i = 0;
            for (; i < strlen(line) && line[i] != ' '; day_nb *= 10, day_nb += (line[i] - 48), i++);
            for (i++; i < strlen(line) && line[i] != ' ' && line[i] != '\n'; part_nb *= 10, part_nb += line[i] - 48, i++);

            if (day_nb == 1)
                day1(part_nb);
            else if (day_nb == 2)
                day2(part_nb);
            else if (day_nb == 3)
                day3(part_nb);
            else if (day_nb == 4)
                day4(part_nb);
            else if (day_nb == 5)
                day5(part_nb);
            else if (day_nb == 6)
                day6(part_nb);
            else if (day_nb == 7)
                day7(part_nb);
            else if (day_nb == 8)
                day8(part_nb);
            else if (day_nb == 9)
                day9(part_nb);
            else if (day_nb == 10)
                day10(part_nb);
            else if (day_nb == 11)
                day11(part_nb);
            else if(day_nb == 12)
                day12(part_nb);
            else
                printf("This day has not been done yet or doesn't exist.\n");
        }
    }

    return 0;
}
