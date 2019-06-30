export LD_LIBRARY_PATH=${PWD}/SFML/lib

g++ main.cpp -ISFML/include -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system