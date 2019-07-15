/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:40:17 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/10 10:04:57 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeFLTK.hpp"

int main(int ac, char* av[]) {
    if (ac == 3) {
        if (ac == 3) {
            try {
                SnakeFLTK ssdl(std::stoi(av[1]), std::stoi(av[2]));
            } catch (const SnakeFLTK::SnakeFLTKException& e) {
                std::cerr << e.what() << '\n';
                return -1;
            }
        }
    }
    return 0;
}
