/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSDL.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:21:34 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/30 15:28:55 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKESDL_HPP
#define SNAKESDL_HPP

#include <SDL.h>
#include <Snake.hpp>

enum E_KEYS {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT
};

typedef struct SVertex {
    float x1;
    float y1;
    float x2;
    float y2;
} TVertex;

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
    SnakeSDL(std::vector<TVertex> &);
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