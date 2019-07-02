/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSDL.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:21:34 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/01 22:20:39 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKESDL_HPP
#define SNAKESDL_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <Snake.hpp>

class SnakeSDL {
   private:
    std::vector<TVertex> *_vertex;
    SDL_Window *_display;
    SDL_Renderer *_renderer;
    // SDL_Event _event;
    Uint32 _start;
    Uint32 _now;
    TVertex _food;
    int WINW;
    int WINH;

    bool *_key;
    int _prevKey;
    bool _doExit;
    float _speed;
    int _score;

   public:
    class SnakeSDLException : std::exception {
       private:
        std::string _exc;

       public:
        SnakeSDLException(std::string);
        SnakeSDLException(SnakeSDLException const &);
        SnakeSDLException &operator=(SnakeSDLException const &);
        virtual const char *what() const throw();
    };

    SnakeSDL(const int, const int);
    SnakeSDL(SnakeT);
    SnakeSDL(SnakeSDL const &);
    SnakeSDL &operator=(SnakeSDL const &);
    ~SnakeSDL();

    void init();
    // void drawRect(TVertex &, ALLEGRO_COLOR);
    bool checkFood();
    void randFood();
    bool moveHead(int);
    bool checkCollusion(TVertex &);
};

#endif  //SNAKESDL_HPP