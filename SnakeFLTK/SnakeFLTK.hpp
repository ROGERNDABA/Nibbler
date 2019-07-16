/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeFLTK.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:14:21 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/16 16:33:51 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKEFLTK_HPP
#define SNAKEFLTK_HPP

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <NibblerException.hpp>
#include <Snake.hpp>

class SnakeFLTK {
   private:
    std::vector<TVertex> *_body;
    std::vector<TVertex> *_obstacles;
    Fl_Window *_display;
    // ALLEGRO_TIMER *_timer;
    // ALLEGRO_EVENT_QUEUE *_eQueue;
    // ALLEGRO_SAMPLE *_sample;
    // ALLEGRO_SAMPLE *_sample2;
    TVertex _food;
    TVertex _bonus;
    SnakeT SNAKE;
    int WINW;
    int WINH;

    bool *_key;
    int _prevKey;
    bool _doExit;
    float _speed;
    int _score;
    int _trackFood;
    bool _valBonus;
    int _softExit;

    clock_t _start;
    clock_t _now;

   public:
    class SnakeFLTKException : public NibblerException {
       private:
        std::string _exc;

       public:
        SnakeFLTKException(std::string);
        SnakeFLTKException(SnakeFLTKException const &);
        SnakeFLTKException &operator=(SnakeFLTKException const &);
        virtual const char *what() const throw();
    };

    SnakeFLTK(int w, int h);
    SnakeFLTK(SnakeFLTK const &);
    SnakeFLTK &operator=(SnakeFLTK const &);
    ~SnakeFLTK();

    void init();
};

double diffclock(clock_t, clock_t);
#endif  //SNAKEFLTK_HPP