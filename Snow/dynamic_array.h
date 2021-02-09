#pragma once

typedef void* array_type;

typedef struct {
    array_type* items;      // Adresa s pamětí pro prvky pole
    int size;               // Kolik prvků je aktuálně v poli
    int capacity;           // Kolik prvků se aktuálně vejde to pole
} dynarray;

/**
 * Nainicializuj dynamické pole s danou kapacitou.
 **/
void dynarray_init(dynarray* array, int initial_capacity);

/**
 * Přidej nový prvek do pole. Prvkem musí být adresa naalokovaná pomocí malloc.
 **/
void dynarray_push(dynarray* array, array_type item);

/**
 * Odstraň daný prvek z pole. Při odstranění z pole se zároveň uvolní z paměti.
 **/
void dynarray_remove(dynarray* array, array_type item);

/**
 * Uvolni dynamické pole.
 **/
void dynarray_free(dynarray* array);
