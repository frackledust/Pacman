#include "pac_ghost.h"

void ghosts_init(SDL_Renderer *renderer, Ghosts *ghosts, int number)
{
    ghosts->items = (Ghost *)malloc(number * sizeof(Ghost));
    ghosts->number = number;
    ghosts->moving_ghosts = 0;
    ghosts->found_pacman = false;

    ghosts->texture = IMG_LoadTexture(renderer, GHOST_TEXTURE);
    assert(ghosts->texture);

    ghosts->mouth_sound = Mix_LoadWAV(PACMAN_DEATH_SOUND);
    assert(ghosts->mouth_sound);
}

void ghosts_free(Ghosts *ghosts)
{
    Mix_FreeChunk(ghosts->mouth_sound);
    free(ghosts->items);
}

void ghost_init(Ghost *ghost, int row, int col)
{
    ghost->row = row;
    ghost->col = col;
}

void ghosts_update(Ghosts *ghosts, Grid *board, int get_to_row, int get_to_col)
{
    for (int i = 0; i < ghosts->number; i++)
    {
        Ghost *ghost = &ghosts->items[i];

        //Move ghost
        if (i < ghosts->moving_ghosts)
        {
            if (i % 2 == 1)
            {
                ghost_urgent_move(ghost, board, get_to_row, get_to_col);
            }
            else
            {
                ghost_random_move(ghost, board);
            }
        }

        //Check if ghost arrived at location
        if (successful_catch(ghost, get_to_row, get_to_col))
        {
            ghosts->found_pacman = true;
            Mix_PlayChannel(-1, ghosts->mouth_sound, 0);
        }
    }
}

bool successful_catch(Ghost *ghost, int row, int col)
{
    return equal(ghost->row, ghost->col, row, col);
}

void ghost_random_move(Ghost *ghost, Grid *board)
{
    int moved = false;
    while (!moved)
    {
        int direction = rand() % 4;
        int new_row = ghost->row;
        int new_col = ghost->col;

        get_new_position(&new_row, &new_col, direction);

        moved = ghost_moved(ghost, new_row, new_col, board);
    }
}

void ghost_urgent_move(Ghost *ghost, Grid *board, int get_to_row, int get_to_col)
{
    bool urgent_move = false;
    int moved = false;

    while (!moved)
    {
        //Try move left
        if (!moved && (ghost->row > get_to_row || urgent_move))
        {
            moved = ghost_moved(ghost, ghost->row - 1, ghost->col, board);
        }
        //up
        if (!moved && (ghost->col > get_to_col || urgent_move))
        {
            moved = ghost_moved(ghost, ghost->row, ghost->col - 1, board);
        }
        //right
        if (!moved && (ghost->row < get_to_row || urgent_move))
        {
            moved = ghost_moved(ghost, ghost->row + 1, ghost->col, board);
        }
        //down
        if (!moved && (ghost->col < get_to_col || urgent_move))
        {
            moved = ghost_moved(ghost, ghost->row, ghost->col + 1, board);
        }

        urgent_move = true;
    }
}

bool ghost_moved(Ghost *ghost, int row, int col, Grid *board)
{
    if (isNotWall(row, col, board) && !equal(ghost->last_row, ghost->last_col, row, col))
    {
        ghost->last_row = ghost->row;
        ghost->last_col = ghost->col;

        ghost->row = row;
        ghost->col = col;
        return true;
    }
    return false;
}

void ghosts_render(SDL_Renderer *renderer, Ghosts *ghosts, int unit_height)
{
    for (int i = 0; i < ghosts->number; i++)
    {
        Ghost ghost = ghosts->items[i];

        SDL_Rect dst_rect = {
            .x = ghost.col * unit_height,
            .y = ghost.row * unit_height,
            .w = unit_height,
            .h = unit_height};

        //Render
        SDL_RenderCopyEx(renderer, ghosts->texture, NULL, &dst_rect, 0, NULL, SDL_FLIP_NONE);
    }
}