#include "pac_game.h"

float delta_set(Uint64 *last)
{
    Uint64 now = SDL_GetPerformanceCounter();
    float delta = ((float)(now - *last)) / SDL_GetPerformanceFrequency();
    *last = now;
    return delta;
}

//Game
int game_init(Game *game)
{
    game->running = false;

    //Load input
    if (grid_load(&game->board))
    {
        printf("Gameboard wasn't found.");
        return 1;
    }

    //Create SDL
    game->ctx = sdl_context_init("Program", W_WIDTH, W_HEIGHT);

    //Wall texture
    game->wall = IMG_LoadTexture(game->ctx.renderer, WALL_TEXTURE);
    assert(game->wall);

    //Extra reward texture
    game->extra = IMG_LoadTexture(game->ctx.renderer, EXTRA_TEXTURE);
    assert(game->extra);

    //Font
    game->font = TTF_OpenFont(FONT, 100);
    assert(game->font);

    //Set up game according to the board
    game->unit_height = W_HEIGHT / game->board.rows;
    if (!grid_read(game))
    {
        printf("Gameboard is not suitable.");
        game_free(game);
        return 1;
    }

    //Turn on the game loop
    game->running = true;
    game->started = false;
    game->counter = 0;

    return 0;
}

void game_free(Game *game)
{
    pacman_free(&game->pacman);
    ghosts_free(&game->ghosts);
    free(game->board.items);
    sdl_context_free(&game->ctx);
}

void game_events(Game *game)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            game->running = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                game->started = game->started ^ 1;
                break;
            case SDLK_LEFT:
                game->pacman.direction = LEFT;
                break;
            case SDLK_RIGHT:
                game->pacman.direction = RIGHT;
                break;
            case SDLK_UP:
                game->pacman.direction = UP;
                break;
            case SDLK_DOWN:
                game->pacman.direction = DOWN;
                break;
            default:
                break;
            }
        }
    }
}

void game_update(Game *game, float delta)
{
    counters_update(game, delta);

    while (game->counter > MOVE_SPEED)
    {
        //Reset game if pacman was found
        if (game->ghosts.found_pacman)
        {
            game->pacman.lifes--;
            game_reset(game);
        }
        else
        {
            //Change pacman location and add points
            pacman_update(&game->pacman, &game->board);

            //Change ghosts location and check if they found pacman
            if (game->ghosts.number > 0)
            {
                ghosts_update(&game->ghosts, &game->board, game->pacman.row, game->pacman.col);
            }
        }

        //Update the counter
        game->counter -= MOVE_SPEED;
    }
}

void counters_update(Game *game, float delta)
{
    game->counter += delta;

    //Open the mouth
    if (game->counter > MOUTH_SPEED)
    {
        game->pacman.open = 1;
    }

    //Add one moving ghost
    if (game->ghosts.moving_ghosts < game->ghosts.number)
    {
        game->ghosts.spawn_counter += delta;
        if (game->ghosts.spawn_counter > TIME_TO_MOVE_NEW_GHOST)
        {
            game->ghosts.moving_ghosts++;
            game->ghosts.spawn_counter = 0;
        }
    }
}

void game_reset(Game *game)
{
    free(game->ghosts.items);
    grid_read(game);
    game_render(game);
    game->started = false;
}

void game_render(Game *game)
{
    //Background
    SDL_SetRenderDrawColor(game->ctx.renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->ctx.renderer);

    //Map
    grid_render(game->ctx.renderer, &game->board, game->unit_height, game->wall, game->extra);

    //Pacman
    pacman_render(game->ctx.renderer, &game->pacman, game->unit_height);

    //Ghosts
    ghosts_render(game->ctx.renderer, &game->ghosts, game->unit_height);

    //Statistics
    stats_render(game->ctx.renderer, game->font, &game->pacman);

    //Game over
    if (game->pacman.lifes == 0)
    {
        game_over_render(game->ctx.renderer, game->font);
    }

    SDL_RenderPresent(game->ctx.renderer);
}

void game_intro(Game *game)
{
    game_render(game);
    intro_sound();
}

//Set game according to the game board
int grid_read(Game *game)
{
    Grid grid = game->board;

    //Ghosts init
    ghosts_init(game->ctx.renderer, &game->ghosts, NUMBER_OF_GHOSTS);
    int ghost_count = 0;

    int pacman_count = 0;
    //Go through the grid
    for (int r = 0; r < grid.rows; r++)
    {
        for (int c = 0; c < grid.cols; c++)
        {
            char symbol = grid.items[r * grid.cols + c];
            switch (symbol)
            {
            case 'P':
                if (game->running == false)
                {
                    pacman_init(game->ctx.renderer, &game->pacman, r, c);
                    pacman_count++;
                }
                else
                {
                    pacman_set_to_location(&game->pacman, r, c);
                }
                break;

            case 'G':
                if (ghost_count < NUMBER_OF_GHOSTS)
                {
                    ghost_init(&game->ghosts.items[ghost_count], r, c);
                    ghost_count++;
                }
                break;
            }
        }
    }

    game->ghosts.number = ghost_count;

    return pacman_count;
}

void intro_sound()
{
    Mix_Chunk *intro = Mix_LoadWAV(INTRO_SOUND);
    assert(intro);
    Mix_PlayChannel(-1, intro, 0);
}

void stats_render(SDL_Renderer *renderer, TTF_Font *font, Pacman *pacman)
{
    char buffer[50];

    snprintf(buffer, sizeof(buffer), "Score: %d Lifes: %d", pacman->score, pacman->lifes);

    SDL_Rect text_rect = {
        .x = W_WIDTH - (STATS_WIDTH + 20),
        .y = 100,
        .w = STATS_WIDTH,
        .h = 100};
    sdl_draw_text(renderer, font, white, text_rect, buffer);

    //Print info
    snprintf(buffer, sizeof(buffer), "Press SPACE to start / stop");
    SDL_Rect text2_rect = {
        .x = W_WIDTH - (STATS_WIDTH + 20),
        .y = 200,
        .w = STATS_WIDTH,
        .h = 50};
    sdl_draw_text(renderer, font, magenta, text2_rect, buffer);
}

void game_over_render(SDL_Renderer *renderer, TTF_Font *font)
{
    char buffer[50];

    snprintf(buffer, sizeof(buffer), "GAME OVER");

    SDL_Rect text_rect = {
        .x = W_WIDTH - 200,
        .y = 50,
        .w = 150,
        .h = 50};
    sdl_draw_text(renderer, font, red, text_rect, buffer);
}