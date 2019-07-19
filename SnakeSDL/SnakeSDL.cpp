/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSDL.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:24:19 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/19 12:41:03 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeSDL.hpp"

SnakeSDL::SnakeSDL(int w, int h)
    : _start(0), WINW(w), WINH(h), _prevKey(3), _doExit(false), _speed(8), _score(0), _trackFood(0), _valBonus(false), _softExit(false) {
    _renderer = NULL;
    _display = NULL;
    _buzz = NULL;
    _beep = NULL;
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
    this->_body = tvt;
    this->_obstacles = new std::vector<TVertex>;
    initObstacles();
    this->randFood();
    // this->init();
}

void SnakeSDL::updateSnake(SnakeT Snake) {
    _start = 0;
    _softExit = 0;
    WINW = Snake.WINW;
    WINH = Snake.WINH;
    _body = Snake.body;
    _obstacles = Snake.obstacles;
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
    delete _obstacles;
    delete _body;
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_display)
        SDL_DestroyWindow(_display);
    if (_beep)
        Mix_FreeChunk(_beep);
    if (_buzz)
        Mix_FreeChunk(_buzz);
    Mix_CloseAudio();
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

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        throw SnakeSDLException("SDL could not initialize audio!");
    }

    _display = SDL_CreateWindow("NIBBLER SDL", 0, 0, WINW, WINH + 60, SDL_WINDOW_SHOWN);
    if (_display == NULL) {
        throw SnakeSDLException("Window could not be created!");
    }

    _renderer = SDL_CreateRenderer(_display, -1, SDL_RENDERER_ACCELERATED);

    _beep = Mix_LoadWAV("audio/beep.wav");
    if (!_beep) {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_display);
        throw SnakeSDLException("SDL could init music");
    }
    _beep->volume = 2;

    _buzz = Mix_LoadWAV("audio/error.wav");
    if (!_buzz) {
        Mix_FreeChunk(_beep);
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_display);
        throw SnakeSDLException("SDL could init music");
    }
    _buzz->volume = 30;
}

void SnakeSDL::gameLoop() {
    TTF_Font* font = TTF_OpenFont("fonts/big_noodle_titling.ttf", 18);
    TTF_Font* fontH = TTF_OpenFont("fonts/big_noodle_titling.ttf", 24);
    if (!font) {
        TTF_CloseFont(fontH);
        throw SnakeSDLException("Couldn't open fonts");
    }
    if (!fontH) {
        TTF_CloseFont(font);
        throw SnakeSDLException("Couldn't open fonts");
    }
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Color sdlc = {0, 0, 0, 255};
    SDL_Rect v1, v2;
    v1.x = 20, v1.y = 35, v1.w = 60, v1.h = 20;
    v2.x = (WINW / 2) - 30, v2.y = 5, v2.w = 60, v2.h = 35;

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    int prevEvent = 0;
    while (!_doExit && !_softExit) {
        SDL_Event ev;
        SDL_PollEvent(&ev);

        _now = SDL_GetTicks();
        if (_now >= _start + (1000 * (1.0 / _speed))) {
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
            SDL_RenderClear(_renderer);
            if (checkFood()) {
                randFood();
                Mix_PlayChannel(-1, _beep, 0);
                _score += _speed;
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
            ss << _score;
            std::string s = "Score : " + ss.str();
            surface = TTF_RenderText_Solid(font, s.c_str(), sdlc);
            texture = SDL_CreateTextureFromSurface(_renderer, surface);
            SDL_RenderCopy(_renderer, texture, NULL, &v1);
            s = "SNAKE SDL";
            surface = TTF_RenderText_Solid(font, s.c_str(), sdlc);
            texture = SDL_CreateTextureFromSurface(_renderer, surface);
            SDL_RenderCopy(_renderer, texture, NULL, &v2);

            r.w = 14;
            r.h = 14;

            for (std::vector<TVertex>::iterator it = _obstacles->begin(); it != _obstacles->end(); ++it) {
                r.x = it->x1;
                r.y = it->y1;
                SDL_SetRenderDrawColor(_renderer, 196, 249, 255, 255);
                SDL_RenderFillRect(_renderer, &r);
            }
            for (std::vector<TVertex>::iterator it = _body->begin(); it != _body->end(); ++it) {
                r.x = it->x1;
                r.y = it->y1;
                if (it == _body->begin())
                    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
                else
                    SDL_SetRenderDrawColor(_renderer, 102, 240, 255, 255);
                SDL_RenderFillRect(_renderer, &r);
            }

            r.x = _food.x1, r.y = _food.y1;
            SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(_renderer, &r);

            if (_valBonus) {
                r.x = _bonus.x1, r.y = _bonus.y1, r.w = 20, r.h = 20;
                SDL_SetRenderDrawColor(_renderer, 0, 100, 255, 255);
                SDL_RenderFillRect(_renderer, &r);
            }
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
                case SDLK_1:
                case SDLK_KP_1:
                    _softExit = 1;
                    break;
                case SDLK_2:
                case SDLK_KP_2:
                    _softExit = 2;
                    break;
                case SDLK_3:
                case SDLK_KP_3:
                    _softExit = 3;
                    break;
                case SDLK_ESCAPE: {
                    this->gameOver();
                    _doExit = true, _softExit = 0;
                } break;
            }
            prevEvent = 1;
        }
    }

    SNAKE.WINW = WINW;
    SNAKE.WINH = WINH;
    SNAKE.body = _body;
    SNAKE.obstacles = _obstacles;
    SNAKE.food = _food;
    SNAKE.key = _key;
    SNAKE.prevKey = _prevKey;
    SNAKE.doExit = _doExit;
    SNAKE.speed = _speed;
    SNAKE.score = _score;
    SNAKE.bonus = _bonus;
    SNAKE.trackFood = _trackFood;
    SNAKE.valBonus = _valBonus;
    TTF_CloseFont(font);
    TTF_CloseFont(fontH);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

bool SnakeSDL::checkFood() {
    TVertex tmp = (*_body)[0];
    if (tmp.y1 == _food.y1 &&
        tmp.x1 == _food.x1 &&
        tmp.x2 == _food.x2 &&
        tmp.y2 == _food.y2) {
        _body->push_back(tmp);
        _trackFood++;
        if (_trackFood % 5 == 0) {
            _valBonus = true;
            _speed += 0.2;
        } else {
            _valBonus = false;
        }
        return true;
    } else if (tmp.y1 == _bonus.y1 &&
               tmp.x1 == _bonus.x1 &&
               tmp.x2 == _bonus.x2 &&
               tmp.y2 == _bonus.y2) {
        Mix_PlayChannel(-1, _beep, 0);
        _body->push_back(tmp);
        _speed += 0.2;
        _score += 20;
        _trackFood = 0;
        _valBonus = false;
    }
    return false;
}

bool SnakeSDL::moveHead(int key) {
    TVertex head = *_body->begin();
    TVertex tail = head;
    switch (key) {
        case 0: {
            _body->pop_back();
            tail.y1 = head.y1 - 15;
            tail.y2 = head.y2 - 15;
            _body->insert(_body->begin(), tail);
        } break;
        case 1: {
            _body->pop_back();
            tail.y1 = head.y1 + 15;
            tail.y2 = head.y2 + 15;
            _body->insert(_body->begin(), tail);
        } break;
        case 2: {
            _body->pop_back();
            tail.x1 = head.x1 - 15;
            tail.x2 = head.x2 - 15;
            _body->insert(_body->begin(), tail);
        } break;
        case 3: {
            _body->pop_back();
            tail.x1 = head.x1 + 15;
            tail.x2 = head.x2 + 15;
            _body->insert(_body->begin(), tail);
        } break;
        default: {
            _body->pop_back();
            tail.x1 = head.x1 + 15;
            tail.x2 = head.x2 + 15;
            _body->insert(_body->begin(), tail);
        } break;
    }
    if (checkCollusion(tail)) {
        Mix_PlayChannel(-1, _buzz, 0);
        this->gameOver();
        return true;
    } else {
        return false;
    }
}

bool SnakeSDL::checkCollusion(TVertex& tv) {
    std::vector<TVertex>::iterator it;
    for (it = _body->begin() + 1; it != _body->end(); ++it) {
        if (tv.x1 == it->x1 && tv.x2 == it->x2 && tv.y1 == it->y1 && tv.y2 == it->y2) {
            return true;
        }
    }
    for (it = _obstacles->begin(); it != _obstacles->end(); ++it) {
        if (tv.x1 == it->x1 && tv.x2 == it->x2 && tv.y1 == it->y1 && tv.y2 == it->y2) {
            return true;
        }
    }
    if (tv.x1 < 0 || tv.x2 > WINW || tv.y1 < 60 || tv.y2 > WINH + 60)
        return true;
    return false;
}

void SnakeSDL::initObstacles() {
    TVertex tv;
    TVertex tv2;
    for (int i = 0; i < 10; i++) {
        int rx = 2 + (std::rand() % ((WINW / 15) - 2));
        while (rx >= (((WINW / 15) / 2) - 6) && rx <= (((WINW / 15) / 2) + 6)) {
            rx = 2 + (std::rand() % ((WINW / 15) - 2));
        }
        int ry = 2 + (std::rand() % ((WINH / 15) - 2));

        tv.x1 = rx * 15, tv.y1 = (ry * 15) + 60, tv.x2 = tv.x1 + 15, tv.y2 = tv.y1 + 15;

        tv2.x1 = tv.x1 - 15, tv2.y1 = tv.y1, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
        _obstacles->push_back(tv2);
        tv2.x1 = tv.x1 - 15, tv2.y1 = tv.y1 - 15, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
        _obstacles->push_back(tv2);
        tv2.x1 = tv.x1 - 15, tv2.y1 = tv.y1 + 15, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
        _obstacles->push_back(tv2);

        tv2.x1 = tv.x2, tv2.y1 = tv.y1, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
        _obstacles->push_back(tv2);
        tv2.x1 = tv.x2, tv2.y1 = tv.y1 - 15, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
        _obstacles->push_back(tv2);
        tv2.x1 = tv.x2, tv2.y1 = tv.y1 + 15, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
        _obstacles->push_back(tv2);

        tv2.x1 = tv.x1, tv2.y1 = tv.y1 - 15, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
        _obstacles->push_back(tv2);
        tv2.x1 = tv.x1, tv2.y1 = tv.y2, tv2.x2 = tv2.x1 + 15, tv2.y2 = tv2.y1 + 15;
        _obstacles->push_back(tv2);
        _obstacles->push_back(tv);
    }
}

void SnakeSDL::randFood() {
    int ranx = 1 + (std::rand() % ((WINW / 15) - 1)) - 1;
    int rany = 1 + (std::rand() % ((WINH / 15) - 1)) - 1;
    _food.x1 = ranx * 15;
    _food.x2 = _food.x1 + 15;
    _food.y1 = (rany * 15) + 60;
    _food.y2 = _food.y1 + 15;

    if (_valBonus && _trackFood % 5 == 0) {
        ranx = 1 + (std::rand() % ((WINW / 15) - 1)) - 1;
        rany = 1 + (std::rand() % ((WINH / 15) - 1)) - 1;
        _bonus.x1 = ranx * 15;
        _bonus.x2 = _bonus.x1 + 15;
        _bonus.y1 = (rany * 15) + 60;
        _bonus.y2 = _bonus.y1 + 15;
    }
    std::vector<TVertex>::iterator it;
    for (it = _obstacles->begin(); it != _obstacles->end(); ++it) {
        if (_food.x1 == it->x1 && _food.x2 == it->x2 && _food.y1 == it->y1 && _food.y2 == it->y2) {
            SnakeSDL::randFood();
            return;
        } else if (_bonus.x1 == it->x1 && _bonus.x2 == it->x2 && _bonus.y1 == it->y1 && _bonus.y2 == it->y2) {
            SnakeSDL::randFood();
            return;
        }
    }
}

void SnakeSDL::gameOver() {
    TTF_Font* font = TTF_OpenFont("fonts/XO.TTF", 24);
    TTF_Font* fontH = TTF_OpenFont("fonts/XO.TTF", 60);
    if (!font) {
        TTF_CloseFont(fontH);
        return;
    }
    if (!fontH) {
        TTF_CloseFont(font);
        return;
    }

    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect v1, v2;
    v1.x = (WINW / 2) - 30, v1.y = (WINH / 2), v1.w = 60, v1.h = 30;
    v2.x = (WINW / 2) - 100, v2.y = (WINH / 2) - 120, v2.w = 200, v2.h = 90;

    double start = SDL_GetTicks();
    double now = SDL_GetTicks();

    while ((now - start) <= 5000) {
        SDL_Color sdlc = {255, 255, 255, 255};
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);

        std::stringstream ss;
        ss << _score;
        std::string s = "Score " + ss.str();
        surface = TTF_RenderText_Solid(font, s.c_str(), sdlc);
        texture = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_RenderCopy(_renderer, texture, NULL, &v1);
        s = "GAME OVER";
        sdlc = {255, 0, 0, 255};
        surface = TTF_RenderText_Solid(font, s.c_str(), sdlc);
        texture = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_RenderCopy(_renderer, texture, NULL, &v2);
        SDL_RenderPresent(_renderer);
        now = SDL_GetTicks();
    }

    TTF_CloseFont(font);
    TTF_CloseFont(fontH);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

SnakeT SnakeSDL::getSnake() const {
    return this->SNAKE;
}

int SnakeSDL::getEvent() const {
    return this->_softExit;
}

void SnakeSDL::stop() {
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_display)
        SDL_DestroyWindow(_display);
    if (_beep)
        Mix_FreeChunk(_beep);
    if (_buzz)
        Mix_FreeChunk(_buzz);
    _renderer = NULL;
    _display = NULL;
    _buzz = NULL;
    _beep = NULL;
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

SnakeSDL* createSnake(int w, int h) {
    return new SnakeSDL(w, h);
}

void deleteSnake(SnakeSDL* sa) {
    delete sa;
}
