#include "sdl.h"
#include "snow_f.h"

int main()
{
    int width = 800;
    int height = 600;
    SDL_Context ctx = sdl_context_init("snow", width, height);
    SDL_SetRenderDrawBlendMode(ctx.renderer, SDL_BLENDMODE_BLEND);

    SDL_Texture *snow_pic = IMG_LoadTexture(ctx.renderer, "snowflake.png");
    if (!snow_pic)
    {
        fprintf(stderr, "Obrazek nenalezen\n");
        return 1;
    }

    dynarray snow;
    dynarray_init(&snow, 20);

    int quit = 0;
    //Vytvoření game loop
    while (!quit)
    {
        //Kontrola akce klik
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    Snowflake_create(event.button.x, event.button.y, &snow);
                }
            }
        }

        SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);
        SDL_RenderClear(ctx.renderer);

        //Vykreslení vločkek a posun
        Snow_Print(&snow, ctx.renderer, snow_pic, height);

        SDL_RenderPresent(ctx.renderer);
    }

    Snow_free(&snow);
    sdl_context_free(&ctx);

    return 0;
}