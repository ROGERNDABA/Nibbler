#include <SDL.h>
#include <Snake.hpp>
#include <iostream>
#include "SnakeSDL.hpp"

int main(int ac, char* av[]) {
    if (ac == 3) {
        if (ac == 3) {
            try {
                SnakeSDL ssdl(std::stoi(av[1]), std::stoi(av[2]));
            } catch (const SnakeSDL::SnakeSDLException& e) {
                std::cerr << e.what() << '\n';
                return -1;
            }
        }
    }
    return 0;
}