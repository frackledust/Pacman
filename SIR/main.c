#include <stdio.h>
#include <stdlib.h>
#include "common.h" //struktury
#include "main.h"

int main(int argc, char **argv)
{
    Data data;
    if (Data_create(argc, argv, &data)) //pokud jsou parametry validní, pak naplní data
    {
        printf("Spatne parametry\n");
        return 1;
    }

    sir_allocate(&data); // spočítá hodnoty sir pro každý den

    char *link = argv[4];
    if (sir_draw(data, link, 600, 300, 25)) // vytvoří graf v souboru "link"
    {
        printf("Spatny vystupni soubor. \n");
        return 1;
    }

    free(data.sir);
    return 0;
}