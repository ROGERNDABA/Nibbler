/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:51:21 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/05 15:25:57 by Roger Ndaba      ###   ########.fr       */
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
        nibbler.play(-1);
    }
    return 0;
}
