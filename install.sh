#!/bin/bash

echo -e "\e[31mCleaning up project...\e[0m"
rm -fr CMakeFiles cmake_install.cmake CMakeCache.txt Makefile nibbler lib
make clean -C SnakeAllegro >/dev/null 2>&1 &&
make clean -C SnakeSFML >/dev/null 2>&1 &&
make clean -C SnakeSDL >/dev/null 2>&1
unset LD_LIBRARY_PATH
unset DYLD_LIBRARY_PATH


which -s brew >/dev/null 2>&1
if [[ $? != 0 ]] ; then
    echo -e "\e[33mInstalling Homebrew...\e[0m"
    sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)"
    source ~/.zshrc
else
    brew update
fi

# hash cmake &> /dev/null
# if [ $? -eq 1 ]; then
#     echo -e "\e[33mInstalling CMake...\e[0m"
#     brew install cmake
# fi

# echo -e "\e[33mChecking lib folders...\e[0m"
# if [ -d "$HOME/.brew/Cellar/allegro" ] && [ -d "$HOME/.brew/Cellar/sfml" ] \
#     && [ -d "$HOME/.brew/Cellar/sdl2" ] && [ -d "$HOME/.brew/Cellar/sdl2_mixer" ] \
#     && [ -d "$HOME/.brew/Cellar/sdl2_ttf" ]; then
#     export DYLD_LIBRARY_PATH=$HOME/.brew/Cellar/allegro/*/lib:$HOME/.brew/Cellar/sdl2/*/lib:$HOME/.brew/Cellar/sfml/*/lib
# else
#     echo -e "\e[31mLib folders not found...\e[0m"
#     echo -e "\e[33mInstalling libs. This may take a while...\e[0m"
#     brew install allegro
#     brew install sdl2
#     brew install sfml
#     export DYLD_LIBRARY_PATH=$HOME/.brew/Cellar/allegro/*/lib:$HOME/.brew/Cellar/sdl2/*/lib:$HOME/.brew/Cellar/sfml/*/lib
# fi

# echo -e "\e[33m---Creating project lib folder---\e[0m"
# mkdir lib
# echo -e "\e[33m---Making libSnakeAllegro.so---\e[0m"
# make -C SnakeAllegro >/dev/null 2>&1 && \
# cp -fr SnakeAllegro/libSnakeAllegro.so lib >/dev/null 2>&1
# echo -e "\e[33m---Making libSnakeSDL.so---\e[0m"
# make -C SnakeSDL >/dev/null 2>&1 && \
# cp -fr SnakeSDL/libSnakeSDL.so lib >/dev/null 2>&1
# echo -e "\e[33m---Making libSnakeSFML.so---\e[0m"
# make -C SnakeSFML >/dev/null 2>&1 && \
# cp -fr SnakeSFML/libSnakeSFML.so lib >/dev/null 2>&1
# echo -e "\e[33m---Running CMake---\e[0m"
# cmake .
# echo -e "\e[33m---Making nibbler---\e[0m"
# make