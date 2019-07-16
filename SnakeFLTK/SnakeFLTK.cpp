/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeFLTK.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:17:30 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/16 12:40:35 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeFLTK.hpp"

SnakeFLTK::SnakeFLTK(int w, int h)
    : WINW(w), WINH(h), _prevKey(3), _doExit(false), _speed(8), _score(0), _trackFood(0), _valBonus(false), _softExit(false), _start(0) {
    (void)_prevKey,
        (void)_doExit,
        (void)_speed,
        (void)_score,
        (void)_trackFood,
        (void)_valBonus,
        (void)_softExit,
        _start = clock();

    (void)_food,
        (void)SNAKE,
        (void)_now,
        (void)_bonus;

    _display = NULL;  //, _eQueue = NULL, _timer = NULL, _sample = NULL, _sample2 = NULL;
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
    // this->randFood();
    // this->initObstacles();
    this->init();
}

SnakeFLTK::SnakeFLTKException::SnakeFLTKException(std::string exc) {
    this->_exc = "\033[31m" + exc + "\033[0m";
}

SnakeFLTK::SnakeFLTKException::SnakeFLTKException(SnakeFLTK::SnakeFLTKException const& copy) {
    *this = copy;
}

const char* SnakeFLTK::SnakeFLTKException::what() const throw() {
    return (this->_exc.c_str());
}

SnakeFLTK::SnakeFLTKException& SnakeFLTK::SnakeFLTKException::operator=(SnakeFLTK::SnakeFLTKException const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

SnakeFLTK::~SnakeFLTK() {
    if (_display)
        delete _display;
}

SnakeFLTK::SnakeFLTK(SnakeFLTK const& copy) {
    *this = copy;
};

SnakeFLTK& SnakeFLTK::operator=(SnakeFLTK const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

void SnakeFLTK::init() {
    _display = new Fl_Window(WINW, WINH + 60, "Snake FLTK");
    if (!_display) {
        throw SnakeFLTKException("Could not init fltk display");
    }
    _display->position(0, 0);
    _display->color(FL_BLACK);
    _display->clear_border();

    while (!_doExit) {
        int ev = Fl::event();
        _now = clock();

        if (diffclock(_now, _start) >= (1.0 / 8)) {
            // std::cout << "roger --> " << diffclock(_now, _start) << std::endl;
            _start = _now;
        }
        // for (int i = 0; i < 3; ++i) {
        //     Fl_Box* box = new Fl_Box(20, 40 + i * 120, 300, 100, "Hello, World!");
        //     box->box(FL_UP_BOX);
        //     box->labelfont(FL_BOLD + FL_ITALIC);
        //     box->labelsize(36);
        //     box->labeltype(FL_SHADOW_LABEL);
        // }
        // Fl::handle(FL_KEYDOWN, _display);
        if (ev == FL_KEYBOARD) {
            std::cout << "Hey-----------------" << std::endl;

            int tmp;
            for (int i = 0; i < 4; i++) {
                if (_key[i])
                    tmp = i;
            }
            int key = Fl::event_key();
            switch (key) {
                case FL_Up: {
                    if (tmp != KEY_DOWN && tmp != KEY_UP) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_UP] = true;
                    }
                } break;
                case FL_Down: {
                    if (tmp != KEY_UP && tmp != KEY_DOWN) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_DOWN] = true;
                    }
                } break;
                case FL_Left: {
                    if (tmp != KEY_RIGHT && tmp != KEY_LEFT) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_LEFT] = true;
                    }
                } break;
                case FL_Right: {
                    if (tmp != KEY_LEFT && tmp != KEY_RIGHT) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_RIGHT] = true;
                        std::cout << "Hey++++++++++++++" << std::endl;
                    }
                } break;
                // case FL:
                // case ALLEGRO_KEY_PAD_1:
                //     _softExit = 1;
                //     break;
                // case ALLEGRO_KEY_2:
                // case ALLEGRO_KEY_PAD_2:
                //     _softExit = 2;
                //     break;
                // case ALLEGRO_KEY_3:
                // case ALLEGRO_KEY_PAD_3:
                //     _softExit = 3;
                //     break;
                case FL_Escape: {
                    // this->gameOver();
                    _doExit = true;
                } break;
            }
            // prevEvent = 1;
        }
        _display->end();
        _display->show();
        Fl::check();
    }
}

double diffclock(clock_t clock1, clock_t clock2) {
    double diffticks = clock1 - clock2;
    double diffms = (diffticks) / (CLOCKS_PER_SEC);
    return diffms;
}