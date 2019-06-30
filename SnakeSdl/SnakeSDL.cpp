/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSDL.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:24:19 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/30 15:28:45 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeSDL.hpp"

SnakeSDL::SnakeSDL(int w, int h)
    : WINW(w), WINH(h), _prevKey(3), _doExit(false), _speed(8), _start(0) {
    TVertex tv;

    tv.x1 = (WINW / 2);
    tv.y1 = (WINH / 2);
    tv.x2 = tv.x1 + 20;
    tv.y2 = tv.y1 + 20;
    std::vector<TVertex>* tvt = new std::vector<TVertex>;
    tvt->push_back(tv);
    this->_key = new bool[4];
    std::fill(_key, _key + 4, false);
    _key[3] = true;
    this->_vertex = tvt;
    this->randFood();
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
    delete _vertex;
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
        SDL_Event ev;
        SDL_Event prevEvent;
        SDL_PollEvent(&ev);

        _now = SDL_GetTicks();
        if (_now >= _start + (1000 * (1.0 / _speed))) {
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
            SDL_RenderClear(_renderer);
            if (checkFood()) {
                randFood();
                // _speed += 0.5;
                // al_set_timer_speed(_timer, 1.0 / _speed);
            }

            if (_key[KEY_UP]) {
                _doExit = moveHead(KEY_UP);
            } else if (_key[KEY_DOWN]) {
                _doExit = moveHead(KEY_DOWN);
            } else if (_key[KEY_LEFT]) {
                _doExit = moveHead(KEY_LEFT);
            } else if (_key[KEY_RIGHT]) {
                _doExit = moveHead(KEY_RIGHT);
            } else {
                _doExit = moveHead(-1);
            }
            // logic goes here
            SDL_Rect r;
            r.w = 20;
            r.h = 20;
            for (std::vector<TVertex>::iterator it = _vertex->begin(); it != _vertex->end(); ++it) {
                r.x = it->x1;
                r.y = it->y1;
                if (it == _vertex->begin())
                    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
                else
                    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(_renderer, &r);
            }

            r.x = _food.x1, r.y = _food.y1, r.w = 10, r.h = 10;
            SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(_renderer, &r);
            _start = _now;
            prevEvent = ev;
            SDL_RenderPresent(_renderer);
        } else if (ev.type == SDL_KEYDOWN) {
            int tmp;
            for (int i = 0; i < 4; i++) {
                if (_key[i])
                    tmp = i;
            }
            switch (ev.key.keysym.sym) {
                case SDLK_UP: {
                    if (tmp != KEY_DOWN && tmp != KEY_UP) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_UP] = true;
                    }
                } break;
                case SDLK_DOWN: {
                    if (tmp != KEY_UP && tmp != KEY_DOWN) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_DOWN] = true;
                    }
                } break;
                case SDLK_LEFT: {
                    if (tmp != KEY_RIGHT && tmp != KEY_LEFT) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_LEFT] = true;
                    }
                } break;
                case SDLK_RIGHT: {
                    if (tmp != KEY_LEFT && tmp != KEY_RIGHT) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_RIGHT] = true;
                    }
                } break;
                case SDLK_ESCAPE:
                    _doExit = true;
                    break;
            }
            prevEvent = ev;
        }
    }
}

bool SnakeSDL::checkFood() {
    TVertex tmp = (*_vertex)[0];
    if (_key[KEY_UP]) {
        if (tmp.y1 <= _food.y2 && (_food.x1 >= tmp.x1 && _food.x2 <= tmp.x2)) {
            _vertex->push_back(tmp);
            return true;
        }
    } else if (_key[KEY_DOWN]) {
        if (tmp.y2 >= _food.y1 && (_food.x1 >= tmp.x1 && _food.x2 <= tmp.x2)) {
            _vertex->push_back(tmp);
            return true;
        }
    } else if (_key[KEY_LEFT]) {
        if (tmp.x1 <= _food.x2 && (_food.y1 >= tmp.y1 && _food.y2 <= tmp.y2)) {
            _vertex->push_back(tmp);
            return true;
        }
    } else if (_key[KEY_RIGHT]) {
        if (tmp.x2 >= _food.x1 && (_food.y1 >= tmp.y1 && _food.y2 <= tmp.y2)) {
            _vertex->push_back(tmp);
            return true;
        }
    }
    return false;
}

bool SnakeSDL::moveHead(int key) {
    TVertex head = *_vertex->begin();
    TVertex tail = head;
    switch (key) {
        case 0: {
            _vertex->pop_back();
            tail.y1 = head.y1 - 20;
            tail.y2 = head.y2 - 20;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        case 1: {
            _vertex->pop_back();
            tail.y1 = head.y1 + 20;
            tail.y2 = head.y2 + 20;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        case 2: {
            _vertex->pop_back();
            tail.x1 = head.x1 - 20;
            tail.x2 = head.x2 - 20;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        case 3: {
            _vertex->pop_back();
            tail.x1 = head.x1 + 20;
            tail.x2 = head.x2 + 20;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        default: {
            _vertex->pop_back();
            tail.x1 = head.x1 + 20;
            tail.x2 = head.x2 + 20;
            _vertex->insert(_vertex->begin(), tail);
        } break;
    }
    return (checkCollusion(tail)) ? true : false;
}

bool SnakeSDL::checkCollusion(TVertex& tv) {
    for (std::vector<TVertex>::iterator it = _vertex->begin() + 1; it != _vertex->end(); ++it) {
        if (tv.x1 == it->x1 && tv.x2 == it->x2 && tv.y1 == it->y1 && tv.y2 == it->y2) {
            return true;
        }
    }
    if (tv.x1 <= 0 || tv.x2 >= WINW || tv.y1 <= 0 || tv.y2 >= WINH)
        return true;
    return false;
}

void SnakeSDL::randFood() {
    _food.x1 = ((std::rand() % (WINW - 30) + 1));
    _food.x2 = _food.x1 + 5;
    _food.y1 = ((std::rand() % (WINH - 30) + 1));
    _food.y2 = _food.y1 + 5;
}