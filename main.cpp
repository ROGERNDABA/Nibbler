/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:51:21 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/05 12:32:32 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nibbler.hpp"
#include "NibblerException.hpp"
#include "Snake.hpp"

void dl_error(void) {
    std::cerr << "Error : " << dlerror() << std::endl;
}

int main(int ac, char *av[]) {
    // void *dl_handle;

    if (ac == 4) {
        Nibbler nibbler(av[1], av[2], av[3]);
        // int softExit;
        // int w = std::stoi(av[1]);
        // int h = std::stoi(av[2]);
        // std::string lib = av[3];
        // for (auto &c : lib) c = toupper(c);

        // std::cout << "--> " << w << std::endl;
        // std::cout << "--> " << h << std::endl;
        // std::cout << "--> " << lib << std::endl;

        // std::map<int, std::string> libraries;
        // libraries[0] = "lib/libSnakeAllegro.so";
        // libraries[1] = "lib/libSnakeSDL.so";
        // libraries[2] = "lib/libSnakeSFML.so";
    }

    // dl_handle = dlopen("lib/libSnakeSDL.so", RTLD_LAZY | RTLD_LOCAL);
    // if (!dl_handle) {
    //     dl_error();
    //     exit(EXIT_FAILURE);
    // }

    // SNAKE sa = reinterpret_cast<SNAKE>(dlsym(dl_handle, "createSnake"));
    // Snake *ssa = NULL;
    // if (!sa) {
    //     std::cerr << "Done!" << std::endl;
    // } else {
    //     try {
    //         ssa = sa(900, 600);
    //         ssa->init();
    //         std::cout << "++++++ " << ssa->getEvent() << " ++++++" << std::endl;

    //     } catch (const NibblerException &e) {
    //         std::cerr << e.what() << '\n';
    //     }
    // }
    // DELETESNAKE dsa = reinterpret_cast<DELETESNAKE>(dlsym(dl_handle, "deleteSnake"));

    // dsa(ssa);
    // dlclose(dl_handle);
    return 0;
}
