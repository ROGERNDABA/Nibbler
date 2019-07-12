#include "SnakeFLTK.hpp"

SnakeFLTK::SnakeFLTK(int w, int h) : WINW(w), WINH(h) {
    _display = NULL;
}

SnakeFLTK::SnakeFLTKException::SnakeFLTKException() {}

SnakeFLTK::SnakeFLTKException::SnakeFLTKException(SnakeFLTK::SnakeFLTKException const& copy) {
    *this = copy;
}

const char* SnakeFLTK::SnakeFLTKException::what() const throw() {
    return ("\033[31mSome Exception\033[0m");
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
    _display = new Fl_Window(WINW, WINH, "FLTK Snake");
    if (!_display) {
        throw SnakeFLTKException("")
    }
}