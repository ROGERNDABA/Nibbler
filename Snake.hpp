/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:13:56 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/02 15:15:03 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// #define WINW 900
// #define WINH 600
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

typedef struct SnakeS {
    std::vector<TVertex> *vertex;
    TVertex food;
    bool *key;
    int prevKey;
    bool doExit;
    float speed;
    int score;
} SnakeT;

class Snake {
   public:
    class SnakeException : std::exception {
       private:
        std::string _exc;

       public:
        SnakeException(std::string);
        SnakeException(SnakeException const &);
        SnakeException &operator=(SnakeException const &);
        virtual const char *what() const throw();
    };
    virtual void init() = 0;
    virtual SnakeT getSnake(void) const = 0;
    virtual ~Snake(){};
};

#endif  //SNAKE_HPP