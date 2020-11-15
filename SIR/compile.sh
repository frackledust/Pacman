gcc -fsanitize=address -g -c sir.c -o sir.o
gcc -fsanitize=address -g -c svg.c -o svg.o
gcc -fsanitize=address -g -c main.c -o main.o
gcc sir.o svg.o main.o -fsanitize=address -g -o program