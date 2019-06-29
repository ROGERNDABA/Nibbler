/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSDL.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:24:19 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/29 13:25:28 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeSDL.hpp"

SnakeSDL::SnakeSDL(int w, int h) {}

SnakeSDL::SnakeSDL(std::vector<TVertex>& vertex) {}

SnakeSDL::SnakeSDLException::SnakeSDLException() {
}

SnakeSDL::SnakeSDLException::SnakeSDLException(SnakeSDL::SnakeSDLException const& copy) {
    *this = copy;
}

const char* SnakeSDL::SnakeSDLException::what() const throw() {
    return ("\033[31mSome Exception\033[0m");
}

SnakeSDL::SnakeSDLException& SnakeSDL::SnakeSDLException::operator=(SnakeSDL::SnakeSDLException const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

SnakeSDL::~SnakeSDL() {}

SnakeSDL::SnakeSDL(SnakeSDL const& copy) {
    *this = copy;
};

SnakeSDL& SnakeSDL::operator=(SnakeSDL const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}