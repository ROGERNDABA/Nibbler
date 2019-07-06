#!/bin/bash

dir="lib"

sh clean.sh

if [[ $(which cmake) ]]; then
    rm -fr CMakeFiles $dir cmake_install.cmake CMakeCache.txt
else
    echo -e "\e[32mInstalling CMake..."
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
        sudo apt-get install cmake -y >/dev/null 2>&1
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo "done!"
    fi
fi

export LD_LIBRARY_PATH=$PWD/SnakeAllegro/allegro/lib:$PWD/SnakeSDL/SDL/lib:$PWD/SnakeSFML/SFML/lib

echo -e "\e[33m---Creating lib folder---"
mkdir lib
echo -e "\e[33m---Making libSnakeAllegro.so---"
make -C SnakeAllegro >/dev/null 2>&1 && \
cp -fr SnakeAllegro/libSnakeAllegro.so lib >/dev/null 2>&1
echo -e "\e[33m---Making libSnakeSDL.so---"
make -C SnakeSDL >/dev/null 2>&1 && \
cp -fr SnakeSDL/libSnakeSDL.so lib >/dev/null 2>&1
echo -e "\e[33m---Making libSnakeSFML.so---"
make -C SnakeSFML >/dev/null 2>&1 && \
cp -fr SnakeSFML/libSnakeSFML.so lib >/dev/null 2>&1
echo -e "\e[32m---Running CMake---"
cmake .
echo -e "\e[32m---Making nibbler---\e[0m"
make
# make -C SnakeAllegro