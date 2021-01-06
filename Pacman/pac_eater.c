#include "pac_eater.h"

void pacman_init(SDL_Renderer *renderer, Pacman *pacman, int row, int col)
{
    pacman_set_to_location(pacman, row, col);

    pacman->score = 0;
    pacman->lifes = 3;

    pacman->texture = IMG_LoadTexture(renderer, PACMAN_IMAGE);
    assert(pacman->texture);

    pacman->mouth_sound = Mix_LoadWAV(CHOMP_SOUND);
    assert(pacman->mouth_sound);

    pacman->extra_sound = Mix_LoadWAV(EXTRA_SOUND);
    assert(pacman->extra_sound);
}

void pacman_free(Pacman *pacman)
{
    Mix_FreeChunk(pacman->mouth_sound);
    Mix_FreeChunk(pacman->extra_sound);
}

void pacman_set_to_location(Pacman *pacman, int row, int col)
{
    pacman->row = row;
    pacman->col = col;
    pacman->direction = LEFT;
    pacman->open = 1;
    pacman->mouth_counter = 0;
}

void pacman_update(Pacman *pacman, Grid *board)
{
    int row = pacman->row;
    int col = pacman->col;

    get_new_position(&row, &col, pacman->direction);

    pacman_try_move(row, col, board, pacman);
}

void pacman_try_move(int row, int col, Grid *grid, Pacman *pacman)
{
    char symbol = grid->items[row * grid->cols + col];
    if (symbol != WALL)
    {
        pacman->row = row;
        pacman->col = col;
    }

    if (symbol == COIN)
    {
        pacman->score += 1;
        grid->items[row * grid->cols + col] = TAKEN;
        pacman->open = 0;

        Mix_PlayChannel(-1, pacman->mouth_sound, 0);
    }
    else if (symbol == EXTRA)
    {
        pacman->score += 5;
        grid->items[row * grid->cols + col] = TAKEN;
        pacman->open = 0;

        Mix_PlayChannel(-1, pacman->extra_sound, 0);
    }
}

void pacman_render(SDL_Renderer *renderer, Pacman *pacman, int unit_height)
{
    //Source rectangle
    SDL_Rect src_rect = {
        .x = 500 * pacman->open,
        .y = 0,
        .w = 500,
        .h = 500};

    //Destination rectangle
    SDL_Rect dst_rect = {
        .x = pacman->col * unit_height,
        .y = pacman->row * unit_height,
        .w = unit_height,
        .h = unit_height};

    //Rotate
    int angle = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    switch (pacman->direction)
    {
    case LEFT:
        flip = SDL_FLIP_HORIZONTAL;
        break;
    case RIGHT:
        break;
    case UP:
        angle = 270;
        break;
    case DOWN:
        angle = 90;
    default:
        break;
    }

    //Render
    SDL_RenderCopyEx(renderer, pacman->texture, &src_rect, &dst_rect, angle, NULL, flip);
}