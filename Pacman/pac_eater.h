#pragma once

#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "pac_input.h" //Grid structure
#include "pac_board.h" //Wall signs
#include "pac_links.h"

#define MOUTH_SPEED 200

typedef struct Pacman
{
    int row;
    int col;
    char direction;

    int score;
    int lifes;

    SDL_Texture *texture;
    Mix_Chunk *mouth_sound;
    Mix_Chunk *extra_sound;
    int open;
    float mouth_counter;

} Pacman;

void pacman_init(SDL_Renderer *renderer, Pacman *pacman, int row, int col);
void pacman_free(Pacman *pacman);
void pacman_set_to_location(Pacman *pacman, int row, int col);
void pacman_update(Pacman *pacman, Grid *board);
void pacman_try_move(int row, int col, Grid *grid, Pacman *pacman);
void pacman_render(SDL_Renderer *renderer, Pacman *pacman, int unit_height);