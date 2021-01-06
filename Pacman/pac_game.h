#pragma once
#include <stdbool.h>
#include <assert.h>
#include <unistd.h> //usleep

#include "template/sdl.h" // sdl_context_init
#include "pac_input.h"    // grid_load
#include "pac_board.h"    // grid_render
#include "pac_eater.h"    // pacman_init, pacman_set_to_location, pacman_update, MOUTH_SPEED,
#include "pac_ghost.h"    // ghosts_init, ghost_init
#include "pac_links.h"

#define W_WIDTH 850 //in pixels
#define W_HEIGHT 600
#define STATS_WIDTH 240

#define INTRO_TIME 4 //in s
#define MOVE_SPEED 500 // in ms

typedef struct Game
{
    SDL_Context ctx;
    SDL_Texture *wall;
    SDL_Texture *extra;
    TTF_Font *font;
    int unit_height;

    Grid board;
    bool running;
    bool started;
    float counter;

    Pacman pacman;
    Ghosts ghosts;

} Game;

//Game
int game_init(Game *game);
void game_free(Game *game);
void game_events(Game *game);
void game_update(Game *game, float delta);
void game_reset(Game *game);
void game_render(Game *game);
void game_intro(Game *game);

//Time
float delta_set(Uint64 *last);
void counters_update(Game *game, float delta);

//Set up the game according to the gird
int grid_read(Game *game);

//Audio
void intro_sound();

//Aditional render
void stats_render(SDL_Renderer *renderer, TTF_Font *font, Pacman *pacman);
void game_over_render(SDL_Renderer *renderer, TTF_Font *font);