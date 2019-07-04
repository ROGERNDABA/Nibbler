/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeAllegro.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:37:43 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/04 17:04:22 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeAllegro.hpp"

SnakeAllegro::SnakeAllegro(int w, int h)
    : WINW(w), WINH(h), _prevKey(3), _doExit(false), _speed(8), _score(0), _trackFood(0), _valBonus(false), _start(0) {
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
    this->randFood();
    this->initObstacles();
}

void SnakeAllegro::updateSnake(SnakeT Snake) {
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
    delete _obstacles;
    if (_timer)
        al_destroy_timer(_timer);
    if (_display)
        al_destroy_display(_display);
    if (_eQueue)
        al_destroy_event_queue(_eQueue);
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
    if (!al_init())
        throw SnakeAllegroException("Couldn't create window");

    if (!al_init_primitives_addon())
        throw SnakeAllegro::SnakeAllegroException("Can't init primitives");

    if (!al_init_ttf_addon())
        throw SnakeAllegro::SnakeAllegroException("Can't init ttf adon");

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

    if (!font) {
        throw SnakeAllegroException("Can't load fonts : font");
        al_destroy_font(fontH);
    }

    if (!fontH) {
        throw SnakeAllegroException("Can't load fonts : fontH");
        al_destroy_font(font);
    }

    int prevEvent;
    while (!_doExit) {
        ALLEGRO_EVENT ev;
        al_get_next_event(_eQueue, &ev);
        _now = al_get_time();
        if (_now >= _start + (1.0 / _speed)) {
            if (checkFood()) {
                randFood();
                _score += _speed;
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
            for (std::vector<TVertex>::iterator it = _obstacles->begin();
                 it != _obstacles->end(); ++it) {
                drawRect(*it, al_map_rgb(236, 194, 255));
            }
            for (std::vector<TVertex>::iterator it = _body->begin(); it != _body->end(); ++it) {
                if (it == _body->begin()) {
                    drawRect(*it, al_map_rgb(255, 0, 0));
                } else {
                    drawRect(*it, al_map_rgb(209, 102, 255));
                }
            }
            al_draw_filled_rectangle(0, 0, WINW, 60, al_map_rgb(236, 194, 255));
            al_draw_rectangle(0, 60, WINW, WINH + 60, al_map_rgb(236, 194, 255), 3);
            al_draw_textf(font, al_map_rgb(0, 0, 0), 20, 35, ALLEGRO_ALIGN_LEFT, "Score : %d", _score);
            al_draw_textf(fontH, al_map_rgb(0, 0, 0), WINW / 2, 5, ALLEGRO_ALIGN_CENTER, "SNAKE ALLEGRO");

            drawRect(_food, al_map_rgb(0, 255, 0));
            if (_valBonus) {
                al_draw_filled_circle(_bonus.x1 + 7,
                                      _bonus.y1 + 7, 10, al_map_rgb(0, 100, 255));
            }
            al_flip_display();
            _start = _now;
            prevEvent = 0;
        }
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN && prevEvent == 0) {
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
            prevEvent = 1;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }
    al_destroy_font(font);
    al_destroy_font(fontH);
}

void SnakeAllegro::randFood() {
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
            SnakeAllegro::randFood();
            return;
        } else if (_bonus.x1 == it->x1 && _bonus.x2 == it->x2 && _bonus.y1 == it->y1 && _bonus.y2 == it->y2) {
            SnakeAllegro::randFood();
            return;
        }
    }
}

bool SnakeAllegro::checkFood() {
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
        _body->push_back(tmp);
        _speed += 0.2;
        _score += 20;
        _trackFood = 0;
        _valBonus = false;
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

void SnakeAllegro::initObstacles() {
    TVertex tv;
    TVertex tv2;
    for (int i = 0; i < 10; i++) {
        int rx = 2 + (std::rand() % ((WINW / 15) - 2));
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

SnakeT SnakeAllegro::getSnake() const {
    return this->SNAKE;
}

SnakeAllegro* createSnake(const int w, const int h) {
    return new SnakeAllegro(w, h);
}

void deleteSnake(SnakeAllegro* sa) {
    delete sa;
}
