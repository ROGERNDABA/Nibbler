#include "SnakeFLTK.hpp"
SnakeFLTK::SnakeFLTK(int w, int h)
    : WINW(w), WINH(h), /* _prevKey(3), */ _doExit(false) /*, _speed(8), _score(0), _trackFood(0), _valBonus(false), _softExit(false), _start(0) */ {
    _display = NULL;
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
    return this->_exc.c_str();
}

SnakeFLTK::SnakeFLTKException& SnakeFLTK::SnakeFLTKException::operator=(SnakeFLTK::SnakeFLTKException const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

SnakeFLTK::~SnakeFLTK() {
    if (_display)
        _display->end();
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
    _display = new Fl_Window(900, 600);
    if (!_display)
        throw SnakeFLTKException("Couldn't make fltk window!");
    _display->color(FL_BLACK);
    _display->show();
    Fl::flush();
    // (void)_doExit;
    while (!_doExit) {
        // _display->end();
        // _display->show();
        // Fl::flush();
        std::cout
            << "-->" << std::endl;
    }
}
