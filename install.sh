#!/bin/bash

echo "\033[31mCleaning up project...\e[0m"
rm -fr CMakeFiles cmake_install.cmake CMakeCache.txt Makefile nibbler lib
make clean -C SnakeAllegro >/dev/null 2>&1 &&
make clean -C SnakeSFML >/dev/null 2>&1 &&
make clean -C SnakeSDL >/dev/null 2>&1 &&
make clean -C SnakeFLTK >/dev/null 2>&1

unset LD_LIBRARY_PATH
unset DYLD_LIBRARY_PATH

echo "\033[33mChecking Homebrew...\e[0m"
which -s brew >/dev/null 2>&1
if [[ $? != 0 ]] ; then
    echo "\033[31mHomebrew not found...\e[0m"
    echo "\033[33mInstalling Homebrew...\e[0m"
    sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)"
    source ~/.zshrc
else
    echo "\033[33mUpdating Homebrew...\e[0m"
    # brew update
fi


echo "\033[33mChecking Cmake...\e[0m"
which -s cmake >/dev/null 2>&1
if [[ $? != 0 ]] ; then
    echo "\033[33mInstalling CMake...\e[0m"
    brew install cmake
fi

echo "\033[33mChecking lib folders...\e[0m"
if [ -d "$HOME/.brew/opt/allegro" ] && [ -d "$HOME/.brew/opt/sfml" ] \
    && [ -d "$HOME/.brew/opt/sdl2" ] && [ -d "$HOME/.brew/opt/sdl2_mixer" ] \
    && [ -d "$HOME/.brew/opt/sdl2_ttf" ] && [ -d "$HOME/.brew/opt/fltk" ]; then
    export DYLD_LIBRARY_PATH=$HOME/.brew/opt/allegro/lib:$HOME/.brew/opt/sdl2/lib:$HOME/.brew/opt/sdl2_mixer/lib:$HOME/.brew/opt/sdl2_ttf/lib:$HOME/.brew/opt/sfml/lib:$HOME/.brew/opt/fltk/lib
else
    echo "\033[31mLib folders not found...\e[0m"
    echo "\033[33mInstalling libs. This may take a while...\e[0m"
    brew install allegro
    brew install sdl2
    brew install sdl2_mixer
    brew install sdl2_ttf
    brew install sfml
    brew install fltk
    export DYLD_LIBRARY_PATH=$HOME/.brew/opt/allegro/lib:$HOME/.brew/opt/sdl2/lib:$HOME/.brew/opt/sdl2_mixer/lib:$HOME/.brew/opt/sdl2_ttf/lib:$HOME/.brew/opt/sfml/lib:$HOME/.brew/opt/fltk/lib
fi

echo "\033[33m---Creating project lib folder---\e[0m"
mkdir lib
echo "\033[33m---Making libSnakeFLTK.so---\e[0m"
make -C SnakeFLTK >/dev/null 2>&1 && \
cp -fr SnakeFLTK/libSnakeFLTK.so lib >/dev/null 2>&1
echo "\033[33m---Making libSnakeSDL.so---\e[0m"
make -C SnakeSDL >/dev/null 2>&1 && \
cp -fr SnakeSDL/libSnakeSDL.so lib >/dev/null 2>&1
echo "\033[33m---Making libSnakeSFML.so---\e[0m"
make -C SnakeSFML >/dev/null 2>&1 && \
cp -fr SnakeSFML/libSnakeSFML.so lib >/dev/null 2>&1
echo "\033[33m---Running CMake---\e[0m"
cmake .
echo "\033[33m---Making nibbler---\e[0m"
make