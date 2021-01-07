Pacman
Pavlína Smolková (07.01.2021)

Jednoduchá SDL hra Pacman - postava se snaží sbírat body a vyhnout se duchům

Funkce:
1) načtení mapy z txt souboru   - první dvě čísla = počet řádků a počet sloupců
                                (počet řádků by neměl být vyšší než počet sloupců)
                                - značky:   P - Pacman spawn point
                                            G - Ghost spawn point
                                            W - Wall
                                            E - Extra reward (diamant)
                                            T - Taken (políčko bez bodu)

2) pohyb pacmana na mapě        - hra se spustí/zastaví stisknutím klávesy SPACE
                                - při začátku se pacman pohybuje vlevo
                                - změna směru šipkami na klávesnici

3) score                        - bod = score +1
                                - diamant = score + 5
                                    + schopnost pacmana jíst duchy na 10 s
                                - duch = score + 20
4) pohyb duchů                  - duchové nemohou procházet zdí ani se vracet
                                - první a třetí duch se pohybují náhodně
                                - druhý a čtvrtý duch se snaží dostat na aktuální pozici pacmana
                                - pokud v módu "chased" první a třetí duch se nehýbou,
                                    druhý a čtvrtý utíkají od pacmana
                                - pokud je duch chycen, přemístí se na svůj spawn
5) pacman chycen                - pokud se pozice ducha rovná pozici pacmana = snížení životu pacmana
                                    a reset pozic postav
6) konec hry                    - pokud pacman ztratí všechny životy, hra se zastaví + vypsáno Game Over


Seznam souborů:

    /A_README.txt
    /CMakeLists.txt

    /pac_main.c                     obsahuje hlavní herní smyčku
    /game_links.h                   obsahuje definice cest k assets souborům
    /pac_game.c, /pac_game.h        funkce obsažené v mainu (iniciace hry, update, render, free)
    /pac_input.c, /pac_input.h      nahrání hracího pole z txt souboru
    /pac_board.c, /pac_board.h      funkce na interakce s hrací plochou
    /pac_eater.c, /pac_eater.h      funkce ovládající pacmana samotného
    /pac_ghost.c, /pac_ghost.h      funkce ovládající duchy

    /template/sdl.c
    /template/sdl.h

    /assets/Arial.ttf
    /assets/ghost.png
    /assets/pacman.png
    /assets/wall.jpg

    /assets/map.txt
    /assets/map_simple.txt
    
    /assets/pacman_chomp.wav
    /assets/pacman_death.wav
    /assets/pacman_extra.wav
    /assets/pacman_intro.wav

    /Build - složka na kompilaci programu
