/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeAllegro.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:37:43 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/03 13:29:26 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeAllegro.hpp"

SnakeAllegro::SnakeAllegro(int w, int h)
    : WINW(w), WINH(h), _prevKey(3), _doExit(false), _speed(10), _score(0) {
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
    this->randFood();
    this->init();
}

SnakeAllegro::SnakeAllegro(SnakeT Snake) {
    _body = Snake.vertex;
    _food = Snake.food;
    _key = Snake.key;
    _prevKey = Snake.prevKey;
    _doExit = Snake.doExit;
    _speed = Snake.speed;
    _score = Snake.score;
}

SnakeAllegro::SnakeAllegroException::SnakeAllegroException(std::string exc) {
    this->_exc = "\033[31m" + exc + "\033[0m";
}

SnakeAllegro::SnakeAllegroException::SnakeAllegroException(SnakeAllegro::SnakeAllegroException const& copy) {
    *this = copy;
}

const char* SnakeAllegro::SnakeAllegroException::what() const throw() {
    return (this->_exc.c_str());
}

SnakeAllegro::SnakeAllegroException& SnakeAllegro::SnakeAllegroException::operator=(SnakeAllegro::SnakeAllegroException const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

SnakeAllegro::~SnakeAllegro() {
    delete _body;
    al_destroy_timer(_timer);
    al_destroy_display(_display);
    al_destroy_event_queue(_eQueue);
    std::cout << "\033[31mGame Over\033[m" << std::endl;
}

SnakeAllegro::SnakeAllegro(SnakeAllegro const& copy) {
    *this = copy;
};

SnakeAllegro& SnakeAllegro::operator=(SnakeAllegro const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

void SnakeAllegro::init() {
    if (!al_init()) {
        // throw SnakeAllegroException("Couldn't create window");
        std::cout << "al_init" << std::endl;
        throw std::exception();
    }

    if (!al_init_primitives_addon()) {
        std::cout << "al_primitives" << std::endl;
        throw std::exception();
        throw SnakeAllegro::SnakeAllegroException("Can't init primitives");
    }

    if (!al_init_ttf_addon()) {
        std::cout << "al_ttf" << std::endl;
        throw std::exception();
        throw SnakeAllegro::SnakeAllegroException("Can't init ttf adon");
    }

    _timer = al_create_timer(1.0 / _speed);
    if (!_timer) {
        al_destroy_display(_display);
        al_destroy_timer(_timer);
        throw SnakeAllegroException("Couldn't init timer");
    }
    if (!al_install_keyboard()) {
        al_destroy_timer(_timer);
        throw SnakeAllegroException("failed to initialize the keyboard!");
    }
    _display = al_create_display(WINW, WINH + 60);
    if (!_display) {
        al_destroy_timer(_timer);
        throw SnakeAllegroException("Couldn't init display");
    }
    al_set_window_title(_display, "Snake Allegro");

    _eQueue = al_create_event_queue();
    if (!_eQueue) {
        al_destroy_display(_display);
        al_destroy_timer(_timer);
        throw SnakeAllegroException("failed to create event_queue!");
    }
    al_register_event_source(_eQueue, al_get_display_event_source(_display));
    al_register_event_source(_eQueue, al_get_keyboard_event_source());
    al_register_event_source(_eQueue, al_get_timer_event_source(_timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(_timer);

    ALLEGRO_FONT* font = NULL;
    ALLEGRO_FONT* fontH = NULL;
    font = al_load_ttf_font("fonts/big_noodle_titling.ttf", 18, ALLEGRO_TTF_MONOCHROME);
    fontH = al_load_ttf_font("fonts/big_noodle_titling.ttf", 24, ALLEGRO_TTF_MONOCHROME);

    if (!font || !fontH) {
        std::cout << "al_font" << std::endl;
        throw SnakeAllegro::SnakeAllegroException("Can't load fonts");
    }
    while (!_doExit) {
        ALLEGRO_EVENT ev;
        ALLEGRO_EVENT prevEvent;
        al_wait_for_event(_eQueue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (checkFood()) {
                randFood();
                // _speed += 0.5;
                _score += _speed;
                // al_set_timer_speed(_timer, 1.0 / _speed);
            }
            al_clear_to_color(al_map_rgb(0, 0, 0));
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
            for (std::vector<TVertex>::iterator it = _body->begin(); it != _body->end(); ++it) {
                if (it == _body->begin()) {
                    drawRect(*it, al_map_rgb(255, 0, 0));
                } else {
                    drawRect(*it, al_map_rgb(209, 102, 255));
                }
            }
            al_draw_filled_rectangle(0, 0, WINW, 60, al_map_rgb(245, 222, 255));
            al_draw_rectangle(0, 60, WINW, WINH + 60, al_map_rgb(245, 222, 255), 3);
            al_draw_textf(font, al_map_rgb(0, 0, 0), 20, 35, ALLEGRO_ALIGN_LEFT, "Score : %d", _score);
            al_draw_textf(fontH, al_map_rgb(0, 0, 0), WINW / 2, 5, ALLEGRO_ALIGN_CENTER, "SNAKE ALLEGRO");

            drawRect(_food, al_map_rgb(255, 255, 255));
            al_flip_display();
            prevEvent = ev;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && prevEvent.type == ALLEGRO_EVENT_TIMER) {
            int tmp;
            for (int i = 0; i < 4; i++) {
                if (_key[i])
                    tmp = i;
            }
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP: {
                    if (tmp != KEY_DOWN && tmp != KEY_UP) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_UP] = true;
                    }
                } break;
                case ALLEGRO_KEY_DOWN: {
                    if (tmp != KEY_UP && tmp != KEY_DOWN) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_DOWN] = true;
                    }
                } break;
                case ALLEGRO_KEY_LEFT: {
                    if (tmp != KEY_RIGHT && tmp != KEY_LEFT) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_LEFT] = true;
                    }
                } break;
                case ALLEGRO_KEY_RIGHT: {
                    if (tmp != KEY_LEFT && tmp != KEY_RIGHT) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_RIGHT] = true;
                    }
                } break;
                case ALLEGRO_KEY_ESCAPE:
                    _doExit = true;
                    break;
            }
            prevEvent = ev;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }
    al_destroy_font(font);
    al_destroy_font(fontH);
}

void SnakeAllegro::randFood() {
    int tmpx = WINW / 15;
    int tmpy = WINH / 15;

    int ranx = 1 + (std::rand() % (tmpx - 1)) - 1;
    int rany = 1 + (std::rand() % (tmpy - 1)) - 1;
    _food.x1 = ranx * 15;
    _food.x2 = _food.x1 + 15;
    _food.y1 = (rany * 15) + 60;
    _food.y2 = _food.y1 + 15;
}

bool SnakeAllegro::checkFood() {
    TVertex tmp = (*_body)[0];
    if (tmp.y1 == _food.y1 &&
        tmp.x1 == _food.x1 &&
        tmp.x2 == _food.x2 &&
        tmp.y2 == _food.y2) {
        _body->push_back(tmp);
        return true;
    }
    return false;
}

void SnakeAllegro::drawRect(TVertex& tv, ALLEGRO_COLOR alC) {
    al_draw_filled_rounded_rectangle(tv.x1, tv.y1, tv.x2 - 1, tv.y2 - 1, 2, 2, alC);
}

bool SnakeAllegro::moveHead(int key) {
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
    return (checkCollusion(tail)) ? true : false;
}

bool SnakeAllegro::checkCollusion(TVertex& tv) {
    for (std::vector<TVertex>::iterator it = _body->begin() + 1; it != _body->end(); ++it) {
        if (tv.x1 == it->x1 && tv.x2 == it->x2 && tv.y1 == it->y1 && tv.y2 == it->y2) {
            return true;
        }
    }
    if (tv.x1 < 0 || tv.x2 > WINW || tv.y1 < 60 || tv.y2 > WINH + 60)
        return true;
    return false;
}

SnakeT SnakeAllegro::getSnake() const {
    return this->SNAKE;
}

SnakeAllegro* createSnake(int w, int h) {
    return new SnakeAllegro(w, h);
}

void deleteSnake(SnakeAllegro* sa) {
    delete sa;
}
