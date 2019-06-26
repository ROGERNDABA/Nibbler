/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:12:47 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/26 19:59:00 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Snake.hpp>
#include "SnakeAllegro.hpp"

int main(int ac, char* av[]) {
    // (void)av;
    (void)ac;

    srand(time(NULL));

    // TVertex tv;
    // tv.x1 = (WINW / 2) - 15;
    // tv.y1 = (WINH / 2) - 15;
    // tv.x2 = tv.x1 + 30;
    // tv.y2 = tv.y1 + 30;

    // std::cout << "- " << tv.x1 << std::endl;
    // std::cout << "- " << tv.y1 << std::endl;
    // std::cout << "- " << tv.x2 << std::endl;
    // std::cout << "- " << tv.y2 << std::endl;

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
