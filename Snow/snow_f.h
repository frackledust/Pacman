#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dynamic_array.h"

typedef struct Snowflake
{
    float x;
    float y;
    int size;
    float speed;
    float rotation;
    float rotspeed;
    dynarray tail;

} Snowflake;

typedef struct Dust
{
    float x;
    float y;
    int duration;
    int red;
    int green;
    int blue;

} Dust;

void Dust_create(Snowflake *s, int number);
void Snowflake_create(int x, int y, dynarray *snow);
void Dust_print(Snowflake *snowflake, SDL_Renderer* renderer);
void Snow_Print(dynarray* snow, SDL_Renderer* renderer, SDL_Texture *snow_pic, int height);
void Snow_free(dynarray* snow);