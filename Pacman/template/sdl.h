#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

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

/**
 * Vykreslí text na zadané pozici a barvě se zadaným fontem.
 **/
void sdl_draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text);
