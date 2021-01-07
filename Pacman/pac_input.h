#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pac_links.h"

typedef struct Grid
{
    char *items;
    int rows;
    int cols;

} Grid;

int grid_load(Grid *grid);
void edge_guard(int *row, int *col, Grid *grid);
void grid_print(Grid grid); // Prints the grid in console