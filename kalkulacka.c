#include <stdio.h>
#include <string.h> //pro strlen
#include <stdlib.h> //atoi

//Make a change?

int create_number(char *priklad, int pozice);
int digits(int cislo);
int priority(char znamenko);
int vypocet(char *postfix, int *cisla);

int main()
{ //Nahrávání příkladu
    char priklad[255];
    int delka;

    printf("Napiš příklad.\n");
    fgets(priklad, sizeof priklad, stdin);
    delka = strlen(priklad); //delka o 1 větší

    char zasobnik[delka];
    int z = -1; //pozice v zásobníku na znaménka

    char postfix[delka];
    int postfix_delka = -1; //pozice v postfix

    int cisla[delka]; //zasobnik na cisla

    //Postfix konfigurace
    for (int i = 0; i < delka - 1; i++)
    {
        printf("Pracuji s %c \n", priklad[i]);

        //Čísla
        if (priklad[i] >= '0' && priklad[i] <= '9')
        {
            postfix_delka++;
            postfix[postfix_delka] = 'c';

            cisla[postfix_delka] = create_number(priklad, i);
            printf("Cislo %d \n", cisla[postfix_delka]);
            printf("Delka cisla je %d\n", digits(cisla[postfix_delka]));
            i += (digits(cisla[postfix_delka]) - 1);
        }

        //Znaménka
        else if (priority(priklad[i]) > 1)
        {
            //Zaporná čísla
            if (priklad[i] == '-' && (i == 0 || priority(priklad[i - 1]) != 0))
            {
                printf("Měním na negative \n");
                priklad[i] = 'n'; //negative
            }

            while (priority(zasobnik[z]) >= priority(priklad[i]))
            {
                postfix_delka++;
                postfix[postfix_delka] = zasobnik[z];
                z--;
            }

            z++;
            zasobnik[z] = priklad[i];
        }

        //Závorky
        else if (priklad[i] == '(')
        {
            z++;
            zasobnik[z] = priklad[i];
        }

        else if (priklad[i] == ')')
        {
            while (zasobnik[z] != '(')
            {
                postfix_delka++;
                postfix[postfix_delka] = zasobnik[z];
                z--;
            }
            if (zasobnik[z] == '(')
            {
                zasobnik[z] = '\0';
                z--;
            }
        }
        else
        {
            printf("Error");
            return (0);
        }
    }

    //Spojení zásobníku a postfixu
    for (z; z > -1; z--)
    {
        postfix_delka++;
        postfix[postfix_delka] = zasobnik[z];
        zasobnik[z] = '\0';
    }

    postfix[postfix_delka + 1] = '\0';

    printf("Počet znaků je %d \n", postfix_delka + 1);
    printf("Postfix je %s \n", postfix);

    //Výpočet
    float output = vypocet(postfix, cisla);
    printf("Výsledek je: %.f \n", output);

    return 0;
}

//Dodatečné funkce

//Vytvoří číslo ze string
int create_number(char *priklad, int pozice)
{
    char *cislo;
    cislo = (char *)malloc(strlen(priklad));

    int cislice = 0;

    while (priklad[pozice] >= '0' && priklad[pozice] <= '9')
    {
        cislo[cislice] = priklad[pozice];

        pozice++;
        cislice++;
    }
    int output = atoi(cislo);
    free(cislo);
    return output;
}

//Priority znamének
int priority(char znamenko)
{
    switch (znamenko)
    {
    case '+':
    case '-':
        return 2;
        break;

    case '*':
    case '/':
        return 3;
        break;
    case 'n':
        return 4;
        break;
    case '(':
        return 1;
        break;
    default:
        return 0; // není znaménko
    }
}

//Zpracuje postfix na výsledek
int vypocet(char *postfix, int *cisla)
{
    int postfix_delka = strlen(postfix);
    float vysledky[postfix_delka];

    int z = -1;

    for (int i = 0; i < postfix_delka; i++)
    {
        switch (postfix[i])
        {
        case 'c':
            z++;
            vysledky[z] = cisla[i];
            printf("Pracuji s %.2f \n", vysledky[z]);
            break;

        case '+':
            printf("%.2f + %.2f \n", vysledky[z - 1], vysledky[z]);
            vysledky[z - 1] = vysledky[z - 1] + vysledky[z];
            z--;
            break;

        case '-':
            printf("%.2f - %.2f \n", vysledky[z - 1], vysledky[z]);
            vysledky[z - 1] = vysledky[z - 1] - vysledky[z];
            z--;
            break;

        case '*':
            printf("%.2f * %.2f \n", vysledky[z - 1], vysledky[z]);
            vysledky[z - 1] = vysledky[z - 1] * vysledky[z];
            z--;
            break;

        case '/':
            printf("%.2f / %.2f \n", vysledky[z - 1], vysledky[z]);
            vysledky[z - 1] = vysledky[z - 1] / vysledky[z];
            z--;
            break;

        case 'n':
            printf("- %.2f \n", vysledky[z]);
            vysledky[z] = vysledky[z] * (-1);
            break;

        default:
            printf("Chyba? \n");
        }

        printf("Mezivýpočet je %.2f zbývá %d čísel\n", vysledky[z], z);
    }

    return vysledky[0];
}

int digits(int cislo)
{
    if (cislo == 0)
        return 0;
    return 1 + digits(cislo / 10);
}