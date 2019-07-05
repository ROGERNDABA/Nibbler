/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:24:48 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/05 12:26:48 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nibbler.hpp"

Nibbler::Nibbler() {}
Nibbler::Nibbler(std::string w, std::string h, std::string lib) {
    try {
        _w = std::stoi(w);
        _h = std::stoi(h);
        if ((_w == 600 && _h == 510) || (_w == 900 && _h == 600)) {  // || (_w == 6 && _h == 510))
            for (auto& c : lib) c = toupper(c);
            this->setup(lib);
            std::cout << "yeah" << std::endl;
        } else {
            throw NibblerExceptionE("Invalid dimensions\nChoose between 600 x 510, 900 x 600 and ");
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "\033[31mInvalid arguments : \n";
        std::cerr << "format : ./nibbler <number> <number> <libname>\033[0m\n";
    } catch (const Nibbler::NibblerExceptionE& e) {
        std::cerr << e.what() << '\n';
    }
    // std::cout << "lib : " << lib << std::endl;
}

Nibbler::NibblerExceptionE::NibblerExceptionE(std::string exc) {
    this->_exc = "\033[31m" + exc + "\033[0m";
}

Nibbler::NibblerExceptionE::NibblerExceptionE(Nibbler::NibblerExceptionE const& copy) {
    *this = copy;
}

const char* Nibbler::NibblerExceptionE::what() const throw() {
    return _exc.c_str();
}

Nibbler::NibblerExceptionE& Nibbler::NibblerExceptionE::operator=(Nibbler::NibblerExceptionE const& rhs) {
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

void Nibbler::setup(std::string lib) {
    _libs[0] = "lib/libSnakeAllegro.so";
    _libs[1] = "lib/libSnakeSDL.so";
    _libs[2] = "lib/libSnakeSFML.so";

    if (lib == "ALLEGRO") {
        _softExit = 1;
    } else if (lib == "SDL") {
        _softExit = 2;
    } else if (lib == "SFML") {
        _softExit = 3;
    } else {
        throw NibblerExceptionE("Invalid library choice");
    }
}