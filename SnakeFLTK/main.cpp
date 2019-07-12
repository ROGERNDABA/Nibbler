#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <iostream>

int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(340, 180);
    // Fl::add_handler(keyhandler);
    window->show();

    bool doExit = false;
    while (!doExit) {
        Fl::check();
        int ev = Fl::event();
        if (ev == FL_SHORTCUT) {
            break;
        }
    }
    window->end();
    window->~Fl_Window();
    return 0;
    // return Fl::run();
}