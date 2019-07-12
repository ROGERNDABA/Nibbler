#ifndef SNAKEFLTK_HPP
#define SNAKEFLTK_HPP

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <fstream>
#include <iostream>

class SnakeFLTK {
   private:
    Fl_Window *_display;

    int WINW;
    int WINH;

   public:
    class SnakeFLTKException : std::exception {
       private:
        std::string _exc;

       public:
        SnakeFLTKException(std::string);
        SnakeFLTKException(SnakeFLTKException const &);
        SnakeFLTKException &operator=(SnakeFLTKException const &);
        virtual const char *what() const throw();
    };

    SnakeFLTK(int, int);
    SnakeFLTK(SnakeFLTK const &);
    SnakeFLTK &operator=(SnakeFLTK const &);
    ~SnakeFLTK();

    void init();
    void updateDisplay();
};

#endif  //SNAKEFLTK_HPP