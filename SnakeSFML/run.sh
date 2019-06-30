export LD_LIBRARY_PATH=${PWD}/SFML/lib

g++  SnakeSFML.cpp main.cpp -I ../ -ISFML/include -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system