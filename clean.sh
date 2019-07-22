#!/bin/bash
# unset LD_LIBRARY_PATH
echo -e "\e[31mCleaning up project...\e[0m"
rm -fr CMakeFiles cmake_install.cmake CMakeCache.txt Makefile nibbler lib
make clean -C SnakeSFML >/dev/null 2>&1 &&
make clean -C SnakeSDL >/dev/null 2>&1 &&
make clean -C SnakeFLTK >/dev/null 2>&1

# rm -fr SnakeAllegro/allegro
# rm -fr SnakeSFML/SFML
# rm -fr SnakeSDL/SDL2
# rm -fr SnakeFLTK/SDL2
