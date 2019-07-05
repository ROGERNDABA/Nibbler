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

int main(int ac, char *av[]) {
    if (ac == 4) {
        Nibbler nibbler(av[1], av[2], av[3]);
        nibbler.play(-1);
    }
    return 0;
}
