#pragma once

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} SDL_Context;

/**
 * Vytvoří SDL kontext, spolu s oknem se zadaným názvem, šířkou a výškou.
 **/
SDL_Context sdl_context_init(const char* window_name, int width, int height);

/**
 * Uvolní SDL kontext.
 **/
void sdl_context_free(SDL_Context* ctx);
