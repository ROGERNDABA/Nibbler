/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:24:48 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/22 10:28:46 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nibbler.hpp"

Nibbler::Nibbler() {}
Nibbler::Nibbler(std::string w, std::string h, std::string lib) : _dl(NULL), _gameSnake(NULL) {
    try {
        _w = std::stoi(w);
        _h = std::stoi(h);
        if ((_w == 600 && _h == 480) || (_w == 900 && _h == 600) || (_w == 1080 && _h == 780)) {
            for (auto& c : lib) c = toupper(c);
            this->setup(lib);
            this->play();
        } else {
            throw NibblerExceptionE("Invalid dimensions\nChoose between 600x480, 900x600 and 1080x780");
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "\033[31mInvalid arguments : \n";
        std::cerr << "format : ./nibbler <number> <number> <libname>\033[0m\n";
    } catch (const Nibbler::NibblerExceptionE& e) {
        std::cerr << e.what() << '\n';
    }
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

Nibbler::~Nibbler() {
    _deleteSnake = reinterpret_cast<DELETESNAKE>(dlsym(_dl, "deleteSnake"));
    if (_gameSnake) {
        _deleteSnake(_gameSnake);
        std::cout << "\033[31mGAME OVER\033[0m" << std::endl;
    }
    if (_dl)
        dlclose(_dl);
}

Nibbler::Nibbler(Nibbler const& copy) {
    *this = copy;
};

Nibbler& Nibbler::operator=(Nibbler const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

void Nibbler::play() {
    while (_softExit) {
        _dl = dlopen(_libs[_softExit].c_str(), RTLD_LAZY | RTLD_LOCAL);
        if (!_dl)
            throw NibblerExceptionE("dl_error : " + std::string(dlerror()));
        _snake = reinterpret_cast<SNAKE>(dlsym(_dl, "createSnake"));
        if (!_snake)
            throw NibblerExceptionE("Some snake Error");
        else {
            try {
                _gameSnake = _snake(_w, _h);
                _gameSnake->init();
                if (_snakeInfo.score != -1)
                    _gameSnake->updateSnake(_snakeInfo);
                _gameSnake->gameLoop();
                _softExit = _gameSnake->getEvent();
                _snakeInfo = _gameSnake->getSnake();
                _gameSnake->stop();
                if (!_softExit) break;
            } catch (const NibblerException& e) {
                std::cerr << e.what() << '\n';
            }
        }
    }
}

void Nibbler::setup(std::string lib) {
    _libs[1] = "lib/libSnakeSDL.so";
    _libs[2] = "lib/libSnakeSFML.so";
    _libs[3] = "lib/libSnakeFLTK.so";

    _snakeInfo.score = -1;

    if (lib == "SDL") {
        _softExit = 1;
    } else if (lib == "SFML") {
        _softExit = 2;
    } else if (lib == "FLTK") {
        _softExit = 3;
    } else {
        throw NibblerExceptionE("Invalid library choice");
    }
}
