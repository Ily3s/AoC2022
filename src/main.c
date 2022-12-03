#include "Common.h"

int main()
{
    bool should_end = false;

    while (!should_end)
    {
        printf("Type <day> <part> or \"quit\"/\"exit\"\n>");
        char line[10];
        fgets(line, 10, stdin);
        if (!strcmp(line, "quit\n") || !strcmp(line, "exit\n") )
        {
            should_end = true;
        }
        else
        {
            int day_nb = line[0] - 48;
            int part_nb = line[2] - 48;

            if (day_nb == 1)
                day1(part_nb);
            else if (day_nb == 2)
                day2(part_nb);
            else if (day_nb == 3)
                day3(part_nb);
            else
                printf("This day has not been done yet or doesn't exist.\n");
        }
    }

    return 0;
}
