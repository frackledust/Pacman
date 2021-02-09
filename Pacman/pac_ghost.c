#include "pac_ghost.h"

void ghosts_init(SDL_Renderer *renderer, Ghosts *ghosts, int number)
{
    ghosts->items = (Ghost *)malloc(number * sizeof(Ghost));
    ghosts->number = number;
    ghosts->moving_ghosts = 0;

    ghosts->found_pacman = false;
    ghosts->chased = false;

    ghosts->texture = IMG_LoadTexture(renderer, GHOST_TEXTURE);
    assert(ghosts->texture);

    ghosts->mouth_sound = Mix_LoadWAV(PACMAN_DEATH_SOUND);
    assert(ghosts->mouth_sound);

    ghosts->eaten_sound = Mix_LoadWAV(GHOST_DEATH_SOUND);
    assert(ghosts->eaten_sound);
}

void ghosts_free(Ghosts *ghosts)
{
    Mix_FreeChunk(ghosts->mouth_sound);
    Mix_FreeChunk(ghosts->eaten_sound);
    free(ghosts->items);
}

void ghost_init(Ghost *ghost, int row, int col)
{
    ghost->row = row;
    ghost->col = col;

    ghost->spawn_row = row;
    ghost->spawn_col = col;
}

void ghost_reset(Ghosts *ghosts, int i)
{
    Ghost caught_ghost = ghosts->items[i];
    ghosts->items[i] = ghosts->items[ghosts->number - 1];

    //Set ghost to spawn
    caught_ghost.row = caught_ghost.spawn_row;
    caught_ghost.col = caught_ghost.spawn_col;

    //Put him at the end of the array
    ghosts->items[ghosts->number - 1] = caught_ghost;

    ghosts->moving_ghosts--;
}

void ghosts_update(Ghosts *ghosts, Grid *board, int get_to_row, int get_to_col, int *score)
{
    for (int i = 0; i < ghosts->number; i++)
    {
        Ghost *ghost = &ghosts->items[i];

        //Move ghost
        if (i < ghosts->moving_ghosts)
        {
            if (i % 2 == 0)
            {
                if (ghosts->chased == false)
                {
                    ghost_random_move(ghost, board);
                }
            }
            else
            {
                ghost_urgent_move(ghost, board, get_to_row, get_to_col, ghosts->chased);
            }
        }

        //Check if ghost arrived at location
        if (successful_catch(ghost, get_to_row, get_to_col))
        {
            if (ghosts->chased)
            { //Ghost got caught
                *score += 20;
                Mix_PlayChannel(-1, ghosts->eaten_sound, 0);
                ghost_reset(ghosts, i);
            }
            else
            { //Ghost caught a pacman
                ghosts->found_pacman = true;
                Mix_PlayChannel(-1, ghosts->mouth_sound, 0);
            }
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
        edge_guard(&new_row, &new_col, board);
        
        moved = ghost_moved(ghost, new_row, new_col, board);
    }
}

void ghost_urgent_move(Ghost *ghost, Grid *board, int get_to_row, int get_to_col, bool chased)
{
    bool urgent_move = false;
    int moved = false;

    int opposite = 1;
    //if ghost is chased, he would go away from get_to_position
    if (chased)
    {
        opposite = -1;
    }

    while (!moved)
    {
        //Get_to_position is on left
        if (!moved && (ghost->row > get_to_row || urgent_move))
        {
            moved = ghost_moved(ghost, ghost->row - 1 * opposite, ghost->col, board);
        }
        //up
        if (!moved && (ghost->col > get_to_col || urgent_move))
        {
            moved = ghost_moved(ghost, ghost->row, ghost->col - 1 * opposite, board);
        }
        //right
        if (!moved && (ghost->row < get_to_row || urgent_move))
        {
            moved = ghost_moved(ghost, ghost->row + 1 * opposite, ghost->col, board);
        }
        //down
        if (!moved && (ghost->col < get_to_col || urgent_move))
        {
            moved = ghost_moved(ghost, ghost->row, ghost->col + 1 * opposite, board);
        }

        urgent_move = true;
    }
}

bool ghost_moved(Ghost *ghost, int row, int col, Grid *board)
{
    //Changes the row/col in case it's out of the grid
    edge_guard(&row, &col, board);

    //Ghost cannot go through walls or to his previous position
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