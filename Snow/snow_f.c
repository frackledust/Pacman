#include "snow_f.h"

void Dust_create(Snowflake *s, int number)
{
    for (int i = 0; i < number; i++)
    {
        Dust *d = (Dust *)malloc(sizeof(Dust));
        d->x = (rand() % s->size) + s->x;
        d->y = (rand() % s->size) + s->y;
        d->duration = rand() % 255;
        d->red = rand() % 255;
        d->green = rand() % 255;
        d->blue = rand() % 255;

        dynarray_push(&s->tail, d);
    }
}

void Snowflake_create(int x, int y, dynarray *snow)
{
    Snowflake *s = (Snowflake *)malloc(sizeof(Snowflake));
    s->size = rand() % 100;
    s->speed = (rand() % 20 + 1) / (float)10;
    s->rotation = rand() % 10 + 1;
    s->rotspeed = (rand() % 10 + 1) / (float)10;
    ;

    s->x = x - s->size / 2;
    s->y = y - s->size / 2;

    dynarray_push(snow, s);
    dynarray_init(&s->tail, 10);
}

void Dust_print(Snowflake *snowflake, SDL_Renderer* renderer)
{
    Dust *dust;

    for (int j = 0; j < snowflake->tail.size; j++)
    {
        dust = snowflake->tail.items[j];

        SDL_Rect dust_rect = {
            .x = dust->x,
            .y = dust->y,
            .w = 3,
            .h = 3};

        SDL_SetRenderDrawColor(renderer, dust->red, dust->green, dust->blue, dust->duration);
        SDL_RenderFillRect(renderer, &dust_rect);

        if (dust->duration <= 0)
        {
            dynarray_remove(&snowflake->tail, dust);
            j--;
        }
        else
        {
            dust->duration--;
        }
    }

    Dust_create(snowflake, 2);
}

void Snow_Print(dynarray* snow, SDL_Renderer* renderer, SDL_Texture *snow_pic, int height)
{
    Snowflake *snowflake;

    for (int i = 0; i < snow->size; i++)
    {   
        printf("Print %d from %d \n", i, snow->size);
        snowflake = snow->items[i];

        SDL_Rect snow_rect = {
            .x = snowflake->x,
            .y = snowflake->y,
            .w = snowflake->size,
            .h = snowflake->size};
        SDL_RenderCopyEx(renderer, snow_pic, NULL, &snow_rect, snowflake->rotation, NULL, SDL_FLIP_NONE);

        //Dust
        Dust_print(snowflake, renderer);

        //Posun vločky
        snowflake->y += snowflake->speed;
        snowflake->rotation += snowflake->rotspeed;

        if (snowflake->y >= height)
        {
            dynarray_free(&snowflake->tail);
            printf("Tail cleared. \n");
            dynarray_remove(snow, snowflake);
            i--;
        }
    }
}

void Snow_free(dynarray* snow)
{
    Snowflake* snowflake;
    for (int i = 0; i < snow->size; i++)
    {
        snowflake = snow->items[i];
        dynarray_free(&snowflake->tail);
        printf("Not finished tail cleared. \n");
    }
    dynarray_free(snow);
    printf("Snow cleared. \n");
}
