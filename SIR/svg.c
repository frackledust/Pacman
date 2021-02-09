#include <stdio.h>
#include "common.h"

int file_open(FILE **input, char *link, char *action)
{
    *input = fopen(link, action);
    if (*input == NULL)
    {
        return 1;
    }
    return 0;
}

void x_axis_draw(FILE *output, int variable, int step, int width, int height, int shift)
{
    fprintf(output, "<line fill='none' stroke='%s' stroke-width='2' x1='%d' x2='%d' y1='%d' y2='%d'></line>", "black", 0, width, height - shift, height - shift);
    int x;
    int y = height - (shift / 2);

    fprintf(output, "<text x='%d' y='%d'>%s</text>", width / 2, height - (shift / 6), "Days");
    for (int i = step; i <= variable; i += step)
    {
        x = shift + i * (width - shift) / variable;
        fprintf(output, "<text x='%d' y='%d'>%d</text>", x, y, i);
    }
}
void y_axis_draw(FILE *output, int variable, int step, int width, int height, int shift)
{
    fprintf(output, "<line fill='none' stroke='%s' stroke-width='2' x1='%d' x2='%d' y1='%d' y2='%d'></line>", "black", shift, shift, 0, height);
    int x = shift / 3;
    int y;

    fprintf(output, "<text x='%d' y='%d'>%s</text>", 0, 10, "Perc.");
    for (int i = step; i < variable; i += step)
    {
        y = height - shift - i * (height - shift) / variable;
        fprintf(output, "<text x='%d' y='%d'>%d</text>", x, y, i);
    }
}
void polyline_draw(Data *data, FILE *output, int width, int height, int shift, char type, char *colour)
{
    float x;
    float y;
    height = height - shift;
    width = width - shift;

    fprintf(output, "<polyline fill='none' stroke='%s' stroke-width='3' points='", colour);
    for (int d = 0; d < data->days; d++)
    {
        x = shift + width * (d) / data->days;
        switch (type)
        {
        case 's':
            y = height * (1 - data->sir[d].s);
            break;
        case 'i':
            y = height * (1 - data->sir[d].i);
            break;
        case 'r':
            y = height * (1 - data->sir[d].r);
            break;
        }
        fprintf(output, "%6f, %6f ", x, y);
    }
    fprintf(output, "'/>");
}

int sir_draw(Data data, char *link, int width, int height, int shift)
{
    FILE *output;
    if (file_open(&output, link, "w"))
    {
        return 1;
    }

    fprintf(output, "<svg width='%d' height='%d' viewBox='0 0 %d %d' xmlns='http://www.w3.org/2000/svg'>", width, height, width, height);
    fprintf(output, "<rect width='%d' height='%d' fill='%s'/>", width, height, "white");
    fprintf(output, "<text x='%d' y='%d'>%d</text>", shift / 2, height - (shift / 2), 0);

    //Osa x
    int step_x = 1;
    if (data.days > 10)
        step_x = 10;
    if (data.days > 100)
        step_x = data.days/10;
    x_axis_draw(output, data.days, step_x, width, height, shift);

    //Osa y
    int step_y = 10;
    y_axis_draw(output, 100, step_y, width, height, shift);

    //Vykreslit data
    polyline_draw(&data, output, width, height, shift, 's', "blue");
    polyline_draw(&data, output, width, height, shift, 'i', "red");
    polyline_draw(&data, output, width, height, shift, 'r', "green");
    fprintf(output, "</svg>");

    fclose(output);
    return 0;
}
