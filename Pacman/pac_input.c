#include "pac_input.h"

int grid_load(Grid *grid)
{
    //Open file
    FILE *input = fopen(MAP, "r");
    if (input == NULL)
    {
        printf("Input file not found.\n");
        return 1;
    }

    //Grid rows, cols
    char buffer[10];
    fgets(buffer, sizeof buffer, input);
    sscanf(buffer, "%d %d", &grid->rows, &grid->cols);

    if (!grid->rows || !grid->cols)
    {
        printf("Cannot find grid measurements.\n");
        return 1;
    };

    grid->items = (char *)malloc(grid->rows * grid->cols * sizeof(char));

    //Fill grid
    for (int row = 0; row < grid->rows; row++)
    {
        char line[grid->cols + 2];
        fgets(line, sizeof line, input);
        strncpy(grid->items + row * grid->cols, line, grid->cols);
    }

    //Free
    fclose(input);
    return 0;
}

void edge_guard(int *row, int *col, Grid *grid)
{
    while (*row >= grid->rows)
    {
        *row = *row - grid->rows;
    }

    while (*row < 0)
    {
        *row = *row + grid->rows;
    }

    while (*col >= grid->cols)
    {
        *col = *col - grid->cols;
    }

    while (*col < 0)
    {
        *col = *col + grid->cols;
    }
}

void grid_print(Grid grid)
{
    for (int r = 0; r < grid.rows; r++)
    {
        for (int c = 0; c < grid.cols; c++)
        {
            printf("%c", grid.items[r * grid.cols + c]);
        }
        printf("\n");
    }
}