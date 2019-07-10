/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:12:47 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/04 16:35:49 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Snake.hpp>
#include "SnakeAllegro.hpp"

int main(int argc, char** argv) {
    srand(time(NULL));
    if (argc == 3) {
        try {
            SnakeAllegro sa(std::stoi(argv[1]), std::stoi(argv[2]));
        } catch (const NibblerException& e) {
            std::cerr << e.what() << '\n';
            return -1;
        }
    }

    return 0;
}
