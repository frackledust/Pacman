cmake_minimum_required(VERSION 3.4)

project(pacman)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")

add_executable(pacman pac_main.c pac_game.c pac_input.c pac_eater.c  pac_board.c pac_ghost.c template/sdl.c)

target_link_libraries(pacman SDL2 SDL2_image SDL2_ttf SDL2_mixer m)