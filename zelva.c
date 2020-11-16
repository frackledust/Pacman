#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void prekazky(char * mrizka, int mrizka_size, int pocet);

int main()
{
    int rows, cols;

    //Načte ze vstupu dvě čísla oddělená mezerou, rows a cols.
    if (scanf("%d %d", &rows, &cols) != 2)
    {
        printf("Error. Ukončuji program. \n");
        return 0;
    }

    //Iniciace mřížky
    char *mrizka = (char *)malloc(rows * cols * sizeof(char));

    for (int i = 0; i < rows * cols; i++)
    {
        mrizka[i] = '.';
    }

    //Iniciace želvy na pozici (0, 0)
    int zelva, zelva_r = 0, zelva_c = 0;

    //Generátor 3 náhodných překážek
    //prekazky(mrizka, rows*cols, 3);

    //Přepis mřížky
    char pokyn;
    do
    {
        zelva = zelva_r * cols + zelva_c;

        //Načtení pokynu
        if (scanf(" %c", &pokyn) != 1)
        {
            printf("Error. Ukončuji program. \n");
            return 0;
        }

        int w, h;   // délka a výška obdelníku

        switch (pokyn)
        {
        //Pohyb
        case '<':
            if (zelva_c != 0 && mrizka[zelva-1]!='#') zelva_c--;
            break;

        case '>':
            if (zelva_c != (cols - 1) && mrizka[zelva+1]!='#') zelva_c++;
            break;

        case '^':
            if (zelva_r != 0 && mrizka[zelva-cols]!='#') zelva_r--;
            break;
            
        case 'v':
            if (zelva_r != (rows - 1) && mrizka[zelva+cols]!='#') zelva_r++;
            break;

        //Kreslení bodu
        case 'o':
            mrizka[zelva] = 'o';
            break;

        //Kreslení obdelníku
        case 'r':

            //Input délka, výška
            if (scanf("%d %d", &w, &h) != 2)
            {
                printf("Error. Ukončuji program. \n");
                return 0;
            }

            if ((zelva_c + w) <= cols && (zelva_r + h) <= rows)
            {
                //Kreslí vodorovné čáry
                for (int c = 0; c < w; c++)
                {
                    mrizka[zelva_r * cols + zelva_c + c] = 'o';
                    mrizka[(zelva_r + h - 1) * cols + zelva_c + c] = 'o';
                }

                //kreslí svislé čáry (bez překrývání)
                for (int r = 1; r < h - 1; r++)
                {
                    mrizka[(zelva_r + r) * cols + zelva_c] = 'o';
                    mrizka[(zelva_r + r) * cols + zelva_c + w - 1] = 'o';
                }
            }

            break;
        }

    } while (pokyn != 'x');

    //Tisk mřížky
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            printf("%c", mrizka[r * cols + c]);
        }
        printf("\n");
    }

    free(mrizka);
    return 0;
}

void prekazky(char * mrizka, int mrizka_size, int pocet)
{
    srand(time(NULL));
    int random_spot;

    for (int i = 0; i < pocet; i++)
    {
        random_spot = rand() % (mrizka_size);
        mrizka[random_spot]= '#';
    }
}