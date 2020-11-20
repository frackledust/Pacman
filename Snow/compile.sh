gcc -fsanitize=address -g -c snow_main.c -o snow_main.o
gcc -fsanitize=address -g -c snow_f.c -o snow_f.o
gcc -fsanitize=address -g -c sdl.c -o sdl.o
gcc -fsanitize=address -g -c dynamic_array.c -o dynamic_array.o
gcc sdl.o dynamic_array.o snow_f.o snow_main.o -fsanitize=address -g -o snow -lSDL2 -lSDL2_image