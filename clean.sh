#!/bin/bash
echo -e "\e[31mCleaning up project...\e[0m"
rm -fr CMakeFiles cmake_install.cmake CMakeCache.txt Makefile nibbler
make clean -C SnakeAllegro >/dev/null 2>&1 &&
make clean-C SnakeSDL >/dev/null 2>&1 