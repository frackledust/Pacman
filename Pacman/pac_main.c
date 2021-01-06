#include "pac_game.h"
//Pacman

int main()
{
    Game game;
    if (game_init(&game))
    {
        return 1;
    }

    game_intro(&game);

    Uint64 last = SDL_GetPerformanceCounter();
    while (game.running)
    {
        //Update time
        float delta_ms = 1000 * delta_set(&last);

        game_events(&game);

        if (game.pacman.lifes > 0 && game.started == true)
        {
            game_update(&game, delta_ms);
            game_render(&game);
        }
    }

    game_free(&game);
    return 0;
}