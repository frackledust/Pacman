#pragma once
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "pac_input.h" //Grid structure

#define WALL 'W'
#define TAKEN 'T'
#define EXTRA 'E'
#define COIN '_'

//Direction 
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

//Colors
#ifndef COLORS
#define COLORS
static const SDL_Color cyan_green = {162, 200, 181, 255};
static const SDL_Color magenta = {255, 0, 255, 255};
static const SDL_Color white = {255, 255, 255, 255};
static const SDL_Color red = {255, 0, 0, 255};
#endif

bool isNotWall(int row, int col, Grid *grid);
bool equal(int row1, int col1, int row2, int col2);
void get_new_position(int *row, int *col, int direction);

void square_texture_render(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int size);
void square_color_render(SDL_Renderer *renderer, SDL_Color color, int x, int y, int size);
void grid_render(SDL_Renderer *renderer, Grid *grid, int unit_height, SDL_Texture *wall, SDL_Texture *extra);