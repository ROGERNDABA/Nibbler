/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeAllegro.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:19:34 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/03 14:12:24 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKEALLEGRO_HPP
#define SNAKEALLEGRO_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <Snake.hpp>

class SnakeAllegro : public Snake {
   private:
    std::vector<TVertex> *_body;
    std::vector<TVertex> *_obstacles;
    ALLEGRO_DISPLAY *_display;
    ALLEGRO_TIMER *_timer;
    ALLEGRO_EVENT_QUEUE *_eQueue;
    TVertex _food;
    SnakeT SNAKE;
    int WINW;
    int WINH;

    bool *_key;
    int _prevKey;
    bool _doExit;
    float _speed;
    int _score;

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

    SnakeAllegro(const int, const int);
    SnakeAllegro(SnakeT, int, int);
    SnakeAllegro(SnakeAllegro const &);
    SnakeAllegro &operator=(SnakeAllegro const &);
    ~SnakeAllegro();

    SnakeT getSnake(void) const;

    void init();
    void initObstacles();
    void drawRect(TVertex &, ALLEGRO_COLOR);
    bool checkFood();
    void randFood();
    bool moveHead(int);
    bool checkCollusion(TVertex &);
};

extern "C" {
SnakeAllegro *createSnake(int, int);
void deleteSnake(SnakeAllegro *);
}

#endif  //SNAKEALLEGRO_HPP