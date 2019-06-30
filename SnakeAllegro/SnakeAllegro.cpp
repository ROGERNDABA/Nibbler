/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeAllegro.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:37:43 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/30 21:37:48 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeAllegro.hpp"

SnakeAllegro::SnakeAllegro(int w, int h)
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
    this->randFood();
    this->init();
}

SnakeAllegro::SnakeAllegro(std::vector<TVertex>& vertex) : _vertex(&vertex) {}

SnakeAllegro::SnakeAllegroException::SnakeAllegroException(std::string exc) {
    this->_exc = "\033[31m" + exc + "\0330m";
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
    delete _vertex;
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
        throw SnakeAllegroException("Couldn't create window");
    }

    if (!al_init_primitives_addon()) {
        throw SnakeAllegro::SnakeAllegroException("Can't init primitives");
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
    _display = al_create_display(WINW, WINH);
    if (!_display) {
        al_destroy_timer(_timer);
        throw SnakeAllegroException("Couldn't init display");
    }

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

    while (!_doExit) {
        ALLEGRO_EVENT ev;
        ALLEGRO_EVENT prevEvent;
        al_wait_for_event(_eQueue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (checkFood()) {
                randFood();
                _speed += 0.5;
                al_set_timer_speed(_timer, 1.0 / _speed);
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
            for (std::vector<TVertex>::iterator it = _vertex->begin(); it != _vertex->end(); ++it) {
                if (it == _vertex->begin()) {
                    drawRect(*it, al_map_rgb(255, 0, 0));
                } else {
                    drawRect(*it, al_map_rgb(255, 255, 255));
                }
            }
            // al_draw_filled_circle(_food.x2, _food.y2, (_food.x2 - _food.x1) / 2, al_map_rgb(255, 0, 255));
            drawRect(_food, al_map_rgb(255, 0, 255));
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
}

void SnakeAllegro::randFood() {
    _food.x1 = ((std::rand() % (WINW - 30) + 1));
    _food.x2 = _food.x1 + 5;
    _food.y1 = ((std::rand() % (WINH - 30) + 1));
    _food.y2 = _food.y1 + 5;
}

bool SnakeAllegro::checkFood() {
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

void SnakeAllegro::drawRect(TVertex& tv, ALLEGRO_COLOR alC) {
    al_draw_filled_rectangle(tv.x1, tv.y1, tv.x2, tv.y2, alC);
}

bool SnakeAllegro::moveHead(int key) {
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

bool SnakeAllegro::checkCollusion(TVertex& tv) {
    for (std::vector<TVertex>::iterator it = _vertex->begin() + 1; it != _vertex->end(); ++it) {
        if (tv.x1 == it->x1 && tv.x2 == it->x2 && tv.y1 == it->y1 && tv.y2 == it->y2) {
            return true;
        }
    }
    if (tv.x1 <= 0 || tv.x2 >= WINW || tv.y1 <= 0 || tv.y2 >= WINH)
        return true;
    return false;
}

SnakeAllegro* createSnakeAllegro(int w, int h) {
    return new SnakeAllegro(w, h);
}

void deleteSnakeAllegro(SnakeAllegro* sa) {
    delete sa;
}
