#include <iostream>
#include "SnakeFLTK.hpp"

int main(int argc, char **argv) {
    SnakeFLTK fltk(900, 600);
    fltk.init();
    while (1) {
        fltk.updateDisplay();
    }
    return 0;
    // return Fl::run();
}