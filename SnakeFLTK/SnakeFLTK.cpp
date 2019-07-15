/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeFLTK.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:17:30 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/15 13:22:55 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeFLTK.hpp"

SnakeFLTK::SnakeFLTK(int w, int h)
    : WINW(w), WINH(h), _prevKey(3), _doExit(false), _speed(8), _score(0), _trackFood(0), _valBonus(false), _softExit(false), _start(0) {
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
    // this->init();
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

SnakeFLTK::~SnakeFLTK() {}

SnakeFLTK::SnakeFLTK(SnakeFLTK const& copy) {
    *this = copy;
};

SnakeFLTK& SnakeFLTK::operator=(SnakeFLTK const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

void SnakeFLTK::init() {
    _display = new Fl_Window(WINW, WINH + 60);
    if (!_display) {
        throw SnakeFLTKException("Could not init fltk display");
    }
    while (!_doExit) {
        int ev = Fl::event();
        // for (int i = 0; i < 3; ++i) {
        //     Fl_Box* box = new Fl_Box(20, 40 + i * 120, 300, 100, "Hello, World!");
        //     box->box(FL_UP_BOX);
        //     box->labelfont(FL_BOLD + FL_ITALIC);
        //     box->labelsize(36);
        //     box->labeltype(FL_SHADOW_LABEL);
        // }
        _display->end();
        _display->show();
        if (ev == FL_SHORTCUT) {
            if (Fl::event_key() == FL_Escape)
                break;
        }
    }
}