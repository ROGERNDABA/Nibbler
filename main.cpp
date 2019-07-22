/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:51:21 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/22 10:35:19 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nibbler.hpp"
#include "NibblerException.hpp"
#include "Snake.hpp"

void dl_error(void) {
    std::cerr << "Error : " << dlerror() << std::endl;
}

int main(int argc, char **argv) {
    if (argc == 4) {
        Nibbler nibbler(argv[1], argv[2], argv[3]);
    } else {
            std::cerr << "\033[31mInvalid argument list" << std::endl;
            std::cerr << "Usage : ./nibbler <width> <height> <lib>" << std::endl;
            std::cerr << "<lib> options : sdl, sfml, fltk\033[0m" << std::endl;
    }
    return 0;
}
