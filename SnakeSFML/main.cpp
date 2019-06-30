/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 15:34:54 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/30 19:37:53 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeSFML.hpp"

int main(int ac, char* av[]) {
    srand(time(NULL));
    if (ac == 3) {
        if (ac == 3) {
            try {
                SnakeSFML ssfml(std::stoi(av[1]), std::stoi(av[2]));
            } catch (const SnakeSFML::SnakeSFMLException& e) {
                std::cerr << e.what() << '\n';
                return -1;
            }
        }
    }
    return 0;
}
