//
// Created by Ilyes on 08/12/2022.
//

#include "../../Common.h"

void day8(enum Part part)
{
    FILE* input = fopen("../src/days/d08/input.txt", "r");
    char line[101];

    char input_map[99][99];
    char output_map[99][99];

    int output = 0;

    for (int i = 0; fgets(line, 101, input); i++)
    {
        for (int j = 0; j < 99; j++)
        {
            input_map[i][j] = line[j];
        }
    }

    for (int i = 0; i < 99; i++)
    {
        for (int j = 0; j < 99; j++)
        {
            output_map[i][j] = 0;
        }
    }

    if (part == PART1)
    {
        for (int i = 0; i < 99; i++)
        {
            char max_in_line = 0;
            for (int j = 0; j < 99; j++)
            {
                output_map[i][j] = (char)(output_map[i][j] || ( input_map[i][j] > max_in_line ));
                max_in_line += ( input_map[i][j] > max_in_line ) * ( input_map[i][j] - max_in_line );
            }

            max_in_line = 0;
            for (int j = 98; j >= 0; j--)
            {
                output_map[i][j] = (char)(output_map[i][j] || ( input_map[i][j] > max_in_line ));
                max_in_line += ( input_map[i][j] > max_in_line ) * ( input_map[i][j] - max_in_line );
            }

            max_in_line = 0;
            for (int j = 0; j < 99; j++)
            {
                output_map[j][i] = (char)(output_map[j][i] || ( input_map[j][i] > max_in_line ));
                max_in_line += ( input_map[j][i] > max_in_line ) * ( input_map[j][i] - max_in_line );
            }

            max_in_line = 0;
            for (int j = 98; j >= 0; j--)
            {
                output_map[j][i] = (char)(output_map[j][i] || ( input_map[j][i] > max_in_line ));
                max_in_line += ( input_map[j][i] > max_in_line ) * ( input_map[j][i] - max_in_line );
            }
        }

        for (int i = 0; i < 99; i++)
        {
            for (int j = 0; j < 99; j++)
            {
                output += output_map[i][j];
            }
        }
    }
    else if (part == PART2)
    {
        for (int i = 0; i < 99; i++)
        {
            for (int j = 0; j < 99; j++)
            {
                int directions[4] = {0, 0, 0, 0};

                for (int k = i - 1; k >= 0; k--, directions[0]++ )
                {
                    if (input_map[k][j] >= input_map[i][j])
                    {
                        directions[0]++;
                        break;
                    }
                }

                for (int k = i + 1; k < 99; k++, directions[1]++ )
                {
                    if (input_map[k][j] >= input_map[i][j])
                    {
                        directions[1]++;
                        break;
                    }
                }

                for (int k = j - 1; k >= 0; k--, directions[2]++ )
                {
                    if (input_map[i][k] >= input_map[i][j])
                    {
                        directions[2]++;
                        break;
                    }
                }

                for (int k = j + 1; k < 99; k++, directions[3]++ )
                {
                    if (input_map[i][k] >= input_map[i][j])
                    {
                        directions[3]++;
                        break;
                    }
                }

                if ((directions[0] * directions[1] * directions[2] * directions[3]) > output)
                    output = (directions[0] * directions[1] * directions[2] * directions[3]);
            }
        }
    }

    printf("%d\n", output);

}