#include "SnakeFLTK.hpp"
#include <time.h>

SnakeFLTK::SnakeFLTK(int w, int h) : WINW(w), WINH(h) {
    _display = NULL;
}

SnakeFLTK::SnakeFLTKException::SnakeFLTKException(std::string exc) {
    this->_exc = "\033[31m" + exc + "\033[0m";
}

SnakeFLTK::SnakeFLTKException::SnakeFLTKException(SnakeFLTK::SnakeFLTKException const& copy) {
    *this = copy;
}

const char* SnakeFLTK::SnakeFLTKException::what() const throw() {
    return this->_exc.c_str();
}

SnakeFLTK::SnakeFLTKException& SnakeFLTK::SnakeFLTKException::operator=(SnakeFLTK::SnakeFLTKException const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

SnakeFLTK::~SnakeFLTK() {
    if (_display) {
        _display->end();
        _display->~Fl_Window();
    }
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
    _display = new Fl_Window(WINW, WINH, "FLTK Snake");
    if (!_display) {
        throw SnakeFLTKException("could not init fltk window");
    }
    _display->color(FL_BLACK);
}

void SnakeFLTK::updateDisplay() {
    int ev = Fl::event();
    fl_rectf(200, 200, 15, 15, 255, 0, 0);
    _display->show();
    Fl::check();
}