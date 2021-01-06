#include "pac_board.h"

bool isNotWall(int row, int col, Grid *grid)
{
    char symbol = grid->items[row * grid->cols + col];
    return (symbol != WALL);
}

void get_new_position(int *row, int *col, int direction)
{
    switch (direction)
    {
    case LEFT:
        *col -= 1;
        break;
    case RIGHT:
        *col += 1;
        break;
    case UP:
        *row -= 1;
        break;
    case DOWN:
        *row += 1;
        break;
    default:
        break;
    }
}

bool equal(int row1, int col1, int row2, int col2)
{
    return row1 == row2 && col1 == col2;
}

void square_color_render(SDL_Renderer *renderer, SDL_Color color, int x, int y, int size)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {
        .x = x,
        .y = y,
        .w = size,
        .h = size};
    SDL_RenderFillRect(renderer, &rect);
}

void square_texture_render(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int size)
{
    SDL_Rect rect = {
        .x = x,
        .y = y,
        .w = size,
        .h = size};
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
}

void grid_render(SDL_Renderer *renderer, Grid *grid, int unit_height, SDL_Texture *wall, SDL_Texture *extra)
{
    for (int r = 0; r < grid->rows; r++)
    {
        for (int c = 0; c < grid->cols; c++)
        {
            char item = grid->items[r * grid->cols + c];

            if (item == WALL)
            {
                square_texture_render(renderer, wall, c * unit_height, r * unit_height, unit_height);
            }
            else if (item == COIN)
            {
                int shift = unit_height / 2;
                square_color_render(renderer, magenta, c * unit_height + shift, r * unit_height + shift, 5);
            }
            else if (item == EXTRA)
            {
                square_texture_render(renderer, extra, c * unit_height, r * unit_height, unit_height);
            }
        }
    }
}