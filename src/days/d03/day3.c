//
// Created by Ilyes on 03/12/2022.
//

#include "../../Common.h"

void day3(enum Part part)
{
    FILE* file = fopen("../src/days/d03/input.txt", "r");

    uint64_t output_sum = 0;

    if (part == PART1)
    {

        char line[100];

        while (fgets(line, 100, file)) {
            int compartment_size = (strlen(line) - 1) / 2;
            for (int i = 0; i < compartment_size; i++) {
                bool has_found = false;
                for (int j = compartment_size; j < 2 * compartment_size; j++) {
                    if (line[i] == line[j]) {
                        output_sum += (line[i] - 65 - 32 * (line[i] / 95)) % 26 + 1 + 26 * (1 - line[i] / 95);
                        has_found = true;
                        break;
                    }
                }
                if (has_found)
                    break;
            }
        }
    }
    else if (part == PART2)
    {
        char line1[100], line2[100], line3[100];
        while (fgets(line1, 100, file) && fgets(line2, 100, file) && fgets(line3, 100, file))
        {
            bool has_found = false;

            for (int i = 0; i < strlen(line1); i++)
            {
                for (int j = 0; j < strlen(line2); j++)
                {
                    if (line1[i] == line2[j])
                    {
                        for (int k = 0; k < strlen(line3); k++)
                        {
                            if (line2[j] == line3[k])
                            {
                                output_sum += (line1[i] - 65 - 32 * (line1[i] / 95)) % 26 + 1 + 26 * (1 - line1[i] / 95);
                                has_found = true;
                                break;
                            }
                        }
                    }
                    if (has_found)
                        break;
                }
                if (has_found)
                    break;
            }
        }
    }

    fclose(file);

    printf("%llu\n", output_sum);
}