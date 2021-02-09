#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

int get_natural_num(char *string, int *num)
{
    int str_len = strlen(string);
    for (int i = 0; i < str_len - 1; i++)
    {
        if (!isdigit(string[i]))
            return 1;
    }

    *num = atoi(string);
    if (*num > 0)
        return 0;

    return 1;
}
int get_float(char *string, float *num)
{
    int str_len = strlen(string);
    int count_dots = 0;
    for (int i = 0; i < str_len - 1; i++)
    {
        if (string[i] == '.' && i != 0 && i != (str_len - 1))
        {
            count_dots++;
        }
        else if (!isdigit(string[i]))
            return 1;
    }

    if (count_dots != 1)
        return 1;

    *num = atof(string);
    if (*num > 0)
        return 0;

    return 1;
}
float control_range(float min, float max, float num)
{
    if (num < min)
    {
        return min;
    }
    else if (num > max)
    {
        return max;
    }
    else
        return num;
}

//Vypočte SIR pro Day
Day Day_create(Data *data, Day yesterday)
{
    Day day;
    float b = data->infections_per_day;
    float y = 1 / (float)data->infectious_days;

    day.s = control_range(0, 1, yesterday.s - b * yesterday.s * yesterday.i);
    day.i = control_range(0, 1, yesterday.i + b * yesterday.s * yesterday.i - y * yesterday.i);
    day.r = control_range(0, 1, yesterday.r + y * yesterday.i);
    return day;
}
//Kontroluje vstup
int Data_create(int argc, char **argv, Data *data)
{
    if (argc != 5)
        return 1;

    int test = 0;
    test += get_natural_num(argv[1], &data->days);
    test += get_natural_num(argv[2], &data->infectious_days);
    test += get_float(argv[3], &data->infections_per_day);
    if (test != 0)
        return 1;

    return 0;
}
//Generuje SIR data
void sir_allocate(Data *data)
{
    data->sir = (Day *)malloc(data->days * sizeof(Day));
    data->sir[0].s = 0.99;
    data->sir[0].i = 0.01;
    data->sir[0].r = 0.00;

    for (int d = 1; d < data->days; d++)
    {
        data->sir[d] = Day_create(data, data->sir[d - 1]);
    }
}