/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSDL.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:24:19 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/01 22:22:13 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeSDL.hpp"

SnakeSDL::SnakeSDL(int w, int h)
    : WINW(w), WINH(h), _prevKey(3), _doExit(false), _speed(10), _start(0), _score(0) {
    TVertex tv;

    tv.x1 = (WINW / 2);
    tv.y1 = (WINH / 2);
    tv.x2 = tv.x1 + 15;
    tv.y2 = tv.y1 + 15;
    std::vector<TVertex>* tvt = new std::vector<TVertex>;
    tvt->push_back(tv);
    this->_key = new bool[4];
    std::fill(_key, _key + 4, false);
    _key[3] = true;
    this->_vertex = tvt;
    this->randFood();
    this->init();
}

SnakeSDL::SnakeSDL(SnakeT Snake) {
    _vertex = Snake.vertex;
    _food = Snake.food;
    _key = Snake.key;
    _prevKey = Snake.prevKey;
    _doExit = Snake.doExit;
    _speed = Snake.speed;
    _score = Snake.score;
}

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
    TTF_Quit();
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

    if (TTF_Init() == -1) {
        throw SnakeSDLException("SDL could not initialize ttf!");
    }

    _display = SDL_CreateWindow("NIBBLER SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINW, WINH + 60, SDL_WINDOW_SHOWN);
    if (_display == NULL) {
        throw SnakeSDLException("Window could not be created!");
    }

    _renderer = SDL_CreateRenderer(_display, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("../fonts/big_noodle_titling.ttf", 18);
    TTF_Font* fontHA = TTF_OpenFont("../fonts/big_noodle_titling.ttf", 24);
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect v1, v2;
    v1.x = 20, v1.y = 35, v1.w = 60, v1.h = 20;
    v2.x = (WINW / 2) - 30, v2.y = 5, v2.w = 60, v2.h = 35;

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    int prevEvent = 0;
    while (!_doExit) {
        SDL_Event ev;
        SDL_PollEvent(&ev);

        _now = SDL_GetTicks();
        if (_now >= _start + (1000 * (1.0 / _speed))) {
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
            SDL_RenderClear(_renderer);
            if (checkFood()) {
                randFood();
                // _speed += 0.5;
                _score += _speed;
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
            SDL_Rect r;
            r.x = 0, r.y = 0, r.w = WINW, r.h = WINH + 60;
            SDL_SetRenderDrawColor(_renderer, 196, 249, 255, 255);
            SDL_RenderFillRect(_renderer, &r);
            r.x = 2, r.y = 60, r.w = WINW - 4, r.h = WINH - 2;
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(_renderer, &r);

            std::stringstream ss;
            std::string s = "Score : " + ss.str();
            surface = TTF_RenderText_Solid(font, s.c_str(), {0, 0, 0});
            texture = SDL_CreateTextureFromSurface(_renderer, surface);
            SDL_RenderCopy(_renderer, texture, NULL, &v1);
            s = "SNAKE SDL";
            surface = TTF_RenderText_Solid(font, s.c_str(), {0, 0, 0});
            texture = SDL_CreateTextureFromSurface(_renderer, surface);
            SDL_RenderCopy(_renderer, texture, NULL, &v2);

            r.w = 14;
            r.h = 14;
            for (std::vector<TVertex>::iterator it = _vertex->begin(); it != _vertex->end(); ++it) {
                r.x = it->x1;
                r.y = it->y1;
                if (it == _vertex->begin())
                    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
                else
                    SDL_SetRenderDrawColor(_renderer, 102, 240, 255, 255);
                SDL_RenderFillRect(_renderer, &r);
            }

            r.x = _food.x1, r.y = _food.y1;
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(_renderer, &r);
            _start = _now;
            prevEvent = 0;
            ev.type = SDL_TEXTINPUT;
            SDL_RenderPresent(_renderer);
        }
        if (ev.type == SDL_KEYDOWN && prevEvent == 0) {
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
            prevEvent = 1;
        }
    }
    TTF_CloseFont(font);
    TTF_CloseFont(fontHA);
    SDL_DestroyTexture(texture);
    // SDL_DestroyTexture(texture2);
    SDL_FreeSurface(surface);
    // SDL_FreeSurface(surface2);
}

bool SnakeSDL::checkFood() {
    TVertex tmp = (*_vertex)[0];
    if (tmp.y1 == _food.y1 &&
        tmp.x1 == _food.x1 &&
        tmp.x2 == _food.x2 &&
        tmp.y2 == _food.y2) {
        _vertex->push_back(tmp);
        return true;
    }
    return false;
}

bool SnakeSDL::moveHead(int key) {
    TVertex head = *_vertex->begin();
    TVertex tail = head;
    switch (key) {
        case 0: {
            _vertex->pop_back();
            tail.y1 = head.y1 - 15;
            tail.y2 = head.y2 - 15;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        case 1: {
            _vertex->pop_back();
            tail.y1 = head.y1 + 15;
            tail.y2 = head.y2 + 15;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        case 2: {
            _vertex->pop_back();
            tail.x1 = head.x1 - 15;
            tail.x2 = head.x2 - 15;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        case 3: {
            _vertex->pop_back();
            tail.x1 = head.x1 + 15;
            tail.x2 = head.x2 + 15;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        default: {
            _vertex->pop_back();
            tail.x1 = head.x1 + 15;
            tail.x2 = head.x2 + 15;
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
    if (tv.x1 < 0 || tv.x2 > WINW || tv.y1 < 60 || tv.y2 > WINH + 60)
        return true;
    return false;
}

void SnakeSDL::randFood() {
    int tmpx = WINW / 15;
    int tmpy = WINH / 15;

    int ranx = 1 + (std::rand() % (tmpx - 1)) - 1;
    int rany = 1 + (std::rand() % (tmpy - 1)) - 1;
    _food.x1 = ranx * 15;
    _food.x2 = _food.x1 + 15;
    _food.y1 = (rany * 15) + 60;
    _food.y2 = _food.y1 + 15;
}
