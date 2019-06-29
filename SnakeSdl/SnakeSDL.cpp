/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSDL.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:24:19 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/29 23:30:00 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeSDL.hpp"

SnakeSDL::SnakeSDL(int w, int h)
    : WINW(w), WINH(h), _prevKey(3), _doExit(false), _speed(8) {
    TVertex tv;

    tv.x1 = (WINW / 2) - 10;
    tv.y1 = (WINH / 2) - 10;
    tv.x2 = tv.x1 + 20;
    tv.y2 = tv.y1 + 20;
    std::vector<TVertex>* tvt = new std::vector<TVertex>;
    tvt->push_back(tv);
    this->_key = new bool[4];
    std::fill(_key, _key + 4, false);
    _key[3] = true;
    this->_vertex = tvt;
    // this->randFood();
    this->init();
}

SnakeSDL::SnakeSDL(std::vector<TVertex>& vertex) : _vertex(&vertex) {}

SnakeSDL::SnakeSDLException::SnakeSDLException(std::string exc) {
    _exc = "\033[31m" + exc + "\033[0m";
}

SnakeSDL::SnakeSDLException::SnakeSDLException(SnakeSDL::SnakeSDLException const& copy) {
    *this = copy;
}

const char* SnakeSDL::SnakeSDLException::what() const throw() {
    return _exc.c_str();
}

SnakeSDL::SnakeSDLException& SnakeSDL::SnakeSDLException::operator=(SnakeSDL::SnakeSDLException const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

SnakeSDL::~SnakeSDL() {
    SDL_DestroyWindow(_display);
    SDL_Quit();
}

SnakeSDL::SnakeSDL(SnakeSDL const& copy) {
    *this = copy;
};

SnakeSDL& SnakeSDL::operator=(SnakeSDL const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

void SnakeSDL::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SnakeSDLException("SDL could not initialize!");
    }

    _display = SDL_CreateWindow("NIBBLER SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINW, WINH, SDL_WINDOW_SHOWN);
    if (_display == NULL) {
        throw SnakeSDLException("Window could not be created!");
    }
    _renderer = SDL_CreateRenderer(_display, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    while (!_doExit) {
        SDL_PollEvent(&_event);

        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);

        _now = SDL_GetTicks();
        if (_now >= _start + (1000 * (1.0 / _speed))) {
            _start = _now;
            // break;
        } else if (_event.type == SDL_KEYDOWN) {
            if (_event.key.keysym.sym == SDLK_ESCAPE)
                _doExit = true;
        }
        // SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
        // SDL_RenderFillRect(renderer, &rect);
        // SDL_RenderPresent(renderer);
    }
}