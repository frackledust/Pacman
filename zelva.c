#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BORDER_SIGN '#'
#define DRAW_SIGN 'o'

typedef struct Grid
{
    char *items;
    int rows;
    int cols;

} Grid;

typedef struct Position
{
    int row;
    int col;

} Position;

void Array_random_change(char* array, int array_size, int num, char symbol);

int main()
{
    Grid grid;

    //Načte ze vstupu dvě čísla oddělená mezerou, rows a cols.
    if (scanf("%d %d", &grid.rows, &grid.cols) != 2)
    {
        printf("Error. Ukončuji program. \n");
        return 0;
    }

    //Iniciace mřížky
    grid.items = (char *)malloc(grid.rows * grid.cols * sizeof(char));

    for (int i = 0; i < grid.rows * grid.cols; i++)
    {
        grid.items[i] = '.';
    }

    //Iniciace želvy na pozici (0, 0)
    Position turtle;
    turtle.row = 0;
    turtle.col = 0;

    //Generátor 3 náhodných překážek
    Array_random_change(grid.items, grid.rows*grid.cols, 3, BORDER_SIGN);

    //Přepis mřížky
    char pokyn;
    do
    {
        int position = turtle.row * grid.cols + turtle.col;

        //Načtení pokynu
        if (scanf(" %c", &pokyn) != 1)
        {
            printf("Error. Ukončuji program. \n");
            return 0;
        }

        int w, h; //délka a šířka obdelníku

        switch (pokyn)
        {
        //Pohyb
        case '<':
            if (turtle.col != 0 && grid.items[position - 1] != BORDER_SIGN)
                turtle.col--;
            break;

        case '>':
            if (turtle.col != (grid.cols - 1) && grid.items[position + 1] != BORDER_SIGN)
                turtle.col++;
            break;

        case '^':
            if (turtle.row != 0 && grid.items[position - grid.cols] != BORDER_SIGN)
                turtle.row--;
            break;

        case 'v':
            if (turtle.row != (grid.rows - 1) && grid.items[position + grid.cols] != BORDER_SIGN)
                turtle.row++;
            break;

        //Kreslení bodu
        case 'o':
            grid.items[position] = DRAW_SIGN;
            break;

        //Kreslení obdelníku
        case 'r':

            //Input délka, výška
            if (scanf("%d %d", &w, &h) != 2)
            {
                printf("Error. Ukončuji program. \n");
                return 0;
            }

            if ((turtle.col + w) <= grid.cols && (turtle.row + h) <= grid.rows)
            {
                //Kreslí vodorovné čáry
                for (int c = 0; c < w; c++)
                {
                    grid.items[turtle.row * grid.cols + turtle.col + c] = DRAW_SIGN;
                    grid.items[(turtle.row + h - 1) * grid.cols + turtle.col + c] = DRAW_SIGN;
                }

                //kreslí svislé čáry (bez překrývání)
                for (int r = 1; r < h - 1; r++)
                {
                    grid.items[(turtle.row + r) * grid.cols + turtle.col] = DRAW_SIGN;
                    grid.items[(turtle.row + r) * grid.cols + turtle.col + w - 1] = DRAW_SIGN;
                }
            }

            break;
        }

    } while (pokyn != 'x');

    //Tisk mřížky
    for (int r = 0; r < grid.rows; r++)
    {
        for (int c = 0; c < grid.cols; c++)
        {
            printf("%c", grid.items[r * grid.cols + c]);
        }
        printf("\n");
    }

    free(grid.items);
    return 0;
}

void Array_random_change(char* array, int array_size, int num, char symbol)
{
    srand(time(NULL));
    int random_spot;

    for (int i = 0; i < num; i++)
    {
        random_spot = rand() % (array_size);
        array[random_spot] = symbol;
    }
}