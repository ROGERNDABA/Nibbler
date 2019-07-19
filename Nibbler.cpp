/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:24:48 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/19 10:36:56 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nibbler.hpp"

Nibbler::Nibbler() {}
Nibbler::Nibbler(std::string w, std::string h, std::string lib) : _dl(NULL), _gameSnake(NULL) {
    try {
        _w = std::stoi(w);
        _h = std::stoi(h);
        if ((_w == 600 && _h == 510) || (_w == 900 && _h == 600)) {  // || (_w == 6 && _h == 510))
            for (auto& c : lib) c = toupper(c);
            this->setup(lib);
            this->play(-1);
        } else {
            throw NibblerExceptionE("Invalid dimensions\nChoose between 600 x 510, 900 x 600 and ");
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
    if (_gameSnake)
        _deleteSnake(_gameSnake);
    dlclose(_dl);
    std::cout << "\033[31mGAME OVER\033[0m" << std::endl;
}

Nibbler::Nibbler(Nibbler const& copy) {
    *this = copy;
};

Nibbler& Nibbler::operator=(Nibbler const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

void Nibbler::play(int softExit) {
    if (softExit != 1 && softExit != 2 && softExit != 3) {
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
                _gameSnake->gameLoop();
                _softExit = _gameSnake->getEvent();
                std::cout << "+++ " << _softExit << std::endl;
                _snakeInfo = _gameSnake->getSnake();
                _gameSnake->stop();
                dlclose(_dl);
                if (_softExit) {
                    Nibbler::play(_softExit);
                }
            } catch (const NibblerException& e) {
                std::cerr << e.what() << '\n';
            }
        }
    } else {
        _dl = dlopen(_libs[_softExit].c_str(), RTLD_LAZY | RTLD_LOCAL);
        if (!_dl) {
            throw NibblerExceptionE("dl_error : " + std::string(dlerror()));
        }
        _snake = reinterpret_cast<SNAKE>(dlsym(_dl, "createSnake"));
        if (!_snake)
            throw NibblerExceptionE("Some snake Error");
        else {
            try {
                _gameSnake = _snake(_w, _h);
                _gameSnake->updateSnake(_snakeInfo);
                _gameSnake->init();
                _gameSnake->gameLoop();
                _softExit = _gameSnake->getEvent();
                _snakeInfo = _gameSnake->getSnake();
                _gameSnake->stop();
                if (_softExit) {
                    Nibbler::play(_softExit);
                }
            } catch (const NibblerException& e) {
                std::cerr << e.what() << '\n';
            }
        }
    }
}

void Nibbler::setup(std::string lib) {
    _libs[1] = "lib/libSnakeFLTK.so";
    _libs[2] = "lib/libSnakeSDL.so";
    _libs[3] = "lib/libSnakeSFML.so";

    if (lib == "FLTK") {
        _softExit = 1;
    } else if (lib == "SDL") {
        _softExit = 2;
    } else if (lib == "SFML") {
        _softExit = 3;
    } else {
        throw NibblerExceptionE("Invalid library choice");
    }
}

/* 
void Nibbler::play(int softExit) {
    try {
        if (softExit != 1 && softExit != 2 && softExit != 3) {
            //     _dl = dlopen(_libs[_softExit].c_str(), RTLD_LAZY | RTLD_LOCAL);
            //     if (!_dl)
            //         throw NibblerExceptionE("dl_error : " + std::string(dlerror()));
            //     _snake = reinterpret_cast<SNAKE>(dlsym(_dl, "createSnake"));
            //     if (!_snake)
            //         throw NibblerExceptionE("Some snake Error");
            //     else {
            _snakes[_softExit]->gameLoop();
            _softExit = _snakes[_softExit]->getEvent();
            _snakeInfo = _snakes[_softExit]->getSnake();
            _snakes[_softExit]->stop();
            if (_softExit)
                Nibbler::play(_softExit);
            // }
        } else {
            //     _dl = dlopen(_libs[_softExit].c_str(), RTLD_LAZY | RTLD_LOCAL);
            //     if (!_dl) {
            //         throw NibblerExceptionE("dl_error : " + std::string(dlerror()));
            //     }
            //     _snake = reinterpret_cast<SNAKE>(dlsym(_dl, "createSnake"));
            //     if (!_snake)
            //         throw NibblerExceptionE("Some snake Error");
            //     else {
            _snakes[_softExit]->updateSnake(_snakeInfo);
            _snakes[_softExit]->gameLoop();
            // _softExit = _snakes[_softExit]->getEvent();
            // _snakeInfo = _snakes[_softExit]->getSnake();
            // _snakes[_softExit]->stop();
            // if (_softExit)
            //     Nibbler::play(_softExit);
            //     }
        }
    } catch (const NibblerExceptionE& e) {
        std::cerr << e.what() << '\n';
    }
} */