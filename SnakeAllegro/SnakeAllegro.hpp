/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeAllegro.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:19:34 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/25 13:07:33 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKEALLEGRO_HPP
#define SNAKEALLEGRO_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_primitives.h>
#include <Snake.hpp>

class SnakeAllegro {
   private:
    std::vector<TVertex> *_vertex;
    ALLEGRO_DISPLAY *_display;
    ALLEGRO_TIMER *_timer;
    ALLEGRO_EVENT_QUEUE *_eQueue;

   public:
    class SnakeAllegroException : std::exception {
       private:
        std::string _exc;

       public:
        SnakeAllegroException(std::string);
        SnakeAllegroException(SnakeAllegroException const &);
        SnakeAllegroException &operator=(SnakeAllegroException const &);
        virtual const char *what() const throw();
    };

    SnakeAllegro(TVertex);
    SnakeAllegro(std::vector<TVertex> &);
    SnakeAllegro(SnakeAllegro const &);
    SnakeAllegro &operator=(SnakeAllegro const &);
    ~SnakeAllegro();

    void init();
};

#endif  //SNAKEALLEGRO_HPP