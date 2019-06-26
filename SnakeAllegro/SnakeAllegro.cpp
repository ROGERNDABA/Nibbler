/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeAllegro.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:37:43 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/26 21:16:22 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeAllegro.hpp"

SnakeAllegro::SnakeAllegro(int w, int h)
    : WINW(w), WINH(h), _prevKey(3), _doExit(false) {
    TVertex tv;

    tv.x1 = (WINW / 2) - 15;
    tv.y1 = (WINH / 2) - 15;
    tv.x2 = tv.x1 + 30;
    tv.y2 = tv.y1 + 30;
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

    _timer = al_create_timer(1.0 / 20);
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
        al_wait_for_event(_eQueue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (checkFood()) {
                randFood();
            }
            if ((*_vertex)[0].x2 >= WINW || (*_vertex)[0].y2 >= WINH)
                break;
            else if ((*_vertex)[0].x1 <= 0 || (*_vertex)[0].y1 <= 0)
                break;

            // TVertex tmpTV;
            // TVertex tmpTV2;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            for (std::vector<TVertex>::iterator it = _vertex->begin(); it != _vertex->end(); ++it) {
                if (it == _vertex->begin()) {
                    if (_key[KEY_UP]) {
                        it->y1 -= 5;
                        it->y2 -= 5;
                    } else if (_key[KEY_DOWN]) {
                        it->y1 += 5;
                        it->y2 += 5;
                    } else if (_key[KEY_LEFT]) {
                        it->x1 -= 5;
                        it->x2 -= 5;
                    } else if (_key[KEY_RIGHT]) {
                        it->x1 += 5;
                        it->x2 += 5;
                    }
                    drawRect(*it, al_map_rgb(255, 0, 0));
                    drawRect(_food, al_map_rgb(255, 0, 255));
                } else {
                    TVertex t = *it;
                    if (t.x1) {
                        //     it->x1 = (it - 1)->x1;
                        //     it->x2 = (it - 1)->x2;
                        //     it->y1 = (it - 1)->y1 + 30;
                        //     it->y2 = (it - 1)->y2 + 30;
                    }
                    drawRect(*it, al_map_rgb(255, 255, 255));
                    drawRect(_food, al_map_rgb(255, 0, 255));
                }
            }
            al_flip_display();
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
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
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }
}

void SnakeAllegro::randFood() {
    _food.x1 = 0 + (std::rand() % (WINW - 30) + 1);
    _food.x2 = _food.x1 + 15;
    _food.y1 = 0 + (std::rand() % (WINH - 30) + 1);
    _food.y2 = _food.y1 + 15;
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

// void SnakeAllegro::drawRect(TVertex& tv, ALLEGRO_COLOR alC) {
//     al_draw_filled_rectangle(tv.x1, tv.y1, tv.x2, tv.y2, alC);
// }
