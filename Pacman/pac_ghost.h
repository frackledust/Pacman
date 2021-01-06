#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h> //malloc
#include <stdbool.h>
#include <assert.h>

#include "pac_input.h" //Grid structure
#include "pac_board.h" //isNotWall, equal, get_new_position
#include "pac_links.h"

#define TIME_TO_MOVE_NEW_GHOST 7000
#define NUMBER_OF_GHOSTS 4

typedef struct Ghost
{
    int row;
    int col;

    int last_row;
    int last_col;

} Ghost;

typedef struct Ghosts
{
    Ghost *items;
    int number;
    int moving_ghosts;
    float spawn_counter;
    bool found_pacman;

    SDL_Texture *texture;
    Mix_Chunk *mouth_sound;

} Ghosts;

void ghost_init(Ghost *ghost, int row, int col);
void ghosts_init(SDL_Renderer *renderer, Ghosts *ghosts, int number);
void ghosts_free(Ghosts *ghosts);

void ghosts_update(Ghosts *ghosts, Grid *board, int get_to_row, int get_to_col);
void ghost_urgent_move(Ghost *ghost, Grid *board, int get_to_row, int get_to_col);
void ghost_random_move(Ghost *ghost, Grid *board);
bool ghost_moved(Ghost *ghost, int row, int col, Grid *board);
bool successful_catch(Ghost *ghost, int row, int col);

void ghosts_render(SDL_Renderer *renderer, Ghosts *ghosts, int unit_height);