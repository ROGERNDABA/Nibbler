/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:24:48 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/02 19:24:59 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nibbler.hpp"

Nibbler::Nibbler() {}

Nibbler::NibblerException::NibblerException() {}

Nibbler::NibblerException::NibblerException(Nibbler::NibblerException const& copy) {
    *this = copy;
}

const char* Nibbler::NibblerException::what() const throw() {
    return ("\033[31mSome Exception\033[0m");
}

Nibbler::NibblerException& Nibbler::NibblerException::operator=(Nibbler::NibblerException const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

Nibbler::~Nibbler() {}

Nibbler::Nibbler(Nibbler const& copy) {
    *this = copy;
};

Nibbler& Nibbler::operator=(Nibbler const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}