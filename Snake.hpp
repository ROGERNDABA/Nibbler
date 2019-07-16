/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:13:56 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/16 12:06:07 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <dlfcn.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
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
    std::vector<TVertex> *body;
    std::vector<TVertex> *obstacles;
    int WINW;
    int WINH;
    TVertex food;
    TVertex bonus;
    bool *key;
    int prevKey;
    bool doExit;
    float speed;
    int score;
    int trackFood;
    bool valBonus;
} SnakeT;

class Snake {
   public:
    virtual void init() = 0;
    virtual SnakeT getSnake(void) const = 0;
    virtual int getEvent(void) const = 0;
    virtual void updateSnake(SnakeT) = 0;
    virtual void stop() = 0;
    virtual ~Snake(){};
};

#endif  //SNAKE_HPP