#include "sdl.h"

#include <assert.h>

SDL_Context sdl_context_init(const char* window_name, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    int flags = MIX_INIT_OGG | MIX_INIT_MOD;
    int init_flags = Mix_Init(flags);
    assert(init_flags == flags);

    int retcode = Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
    assert(!retcode);

    SDL_Window* window = SDL_CreateWindow(window_name, 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    TTF_Init();

    return (SDL_Context) {
        .window = window,
        .renderer = renderer
    };
}
void sdl_context_free(SDL_Context* ctx)
{
    TTF_Quit();
	Mix_Quit();
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    SDL_Quit();
}
void sdl_draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, message, NULL, &location);

    SDL_DestroyTexture(message);
    SDL_FreeSurface(surface);
}
