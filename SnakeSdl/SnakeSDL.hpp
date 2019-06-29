/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSDL.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:21:34 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/29 13:44:49 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKESDL_HPP
#define SNAKESDL_HPP

#include <SDL2/SDL.h>
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
    // ALLEGRO_TIMER *_timer;
    // ALLEGRO_EVENT_QUEUE *_eQueue;
    TVertex _food;
    int WINW;
    int WINH;

    bool *_key;
    int _prevKey;
    bool _doExit;
    float _speed;

   public:
    class SnakeSDLException : std::exception {
       public:
        SnakeSDLException(void);
        SnakeSDLException(SnakeSDLException const &);
        SnakeSDLException &operator=(SnakeSDLException const &);
        virtual const char *what() const throw();
    };

    SnakeSDL(const int, const int);
    SnakeSDL(std::vector<TVertex> &);
    SnakeSDL(SnakeSDL const &);
    SnakeSDL &operator=(SnakeSDL const &);
    ~SnakeSDL();
};

#endif  //SNAKESDL_HPP