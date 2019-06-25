/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:13:56 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/25 12:34:30 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#define WINW 900
#define WINH 600

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

class Snake {
};

#endif  //SNAKE_HPP