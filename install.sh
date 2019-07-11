#!/bin/bash

dir="lib"

echo -e "\e[31mCleaning up project...\e[0m"
rm -fr CMakeFiles cmake_install.cmake CMakeCache.txt Makefile nibbler lib
make clean -C SnakeAllegro >/dev/null 2>&1 &&
make clean -C SnakeSFML >/dev/null 2>&1 &&
make clean -C SnakeSDL >/dev/null 2>&1
unset LD_LIBRARY_PATH

which cmake
if [ $? -eq 0 ]; then
    if [ -d "SnakeAllegro/allegro" -a -d "SnakeSDL/SDL2" -a -d "SnakeSFML/SFML" ]; then
        echo True
    else
        git clone https://github.com/ROGERNDABA/Nibblerlibs.git setup-libs

        mkdir SnakeAllegro/allegro
        cp -fr setup-libs/macos/allegro/* SnakeAllegro/allegro

        mkdir SnakeSDL/SDL2
        cp -fr setup-libs/macos/SDL2/* SnakeSDL/SDL2

        mkdir SnakeSFML/SFML
        cp -fr setup-libs/macos/SFML/* SnakeSFML/SFML
    fi
else
    echo -e "\e[33mInstalling CMake...\e[0m"
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
        sudo apt-get install cmake -y >/dev/null 2>&1
    elif [[ "$USER" == "rmdaba" ]]; then
        brew install cmake
    fi
fi

export LD_LIBRARY_PATH=$PWD/SnakeAllegro/allegro/lib:$PWD/SnakeSDL/SDL/lib:$PWD/SnakeSFML/SFML/lib:$PWD/SnakeFLTK/FLTK/lib
export DYLD_LIBRARY_PATH=$PWD/SnakeAllegro/allegro/lib:$PWD/SnakeSDL/SDL/lib:$PWD/SnakeSFML/SFML/lib:$PWD/SnakeFLTK/FLTK/lib

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
echo -e "\e[33m---Running CMake---"
cmake .
echo -e "\e[33m---Making nibbler---\e[0m"
make
# make -C SnakeAllegro