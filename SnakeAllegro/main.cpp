/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:12:47 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/03 14:14:51 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Snake.hpp>
#include "SnakeAllegro.hpp"

int main(int ac, char* av[]) {
    srand(time(NULL));
    if (ac == 3) {
        try {
            SnakeAllegro sa(std::stoi(av[1]), std::stoi(av[2]));
        } catch (const SnakeAllegro::SnakeAllegroException& e) {
            std::cerr << e.what() << '\n';
            return -1;
        }
    }

    return 0;
}
