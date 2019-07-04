/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSFML.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:13:31 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/04 17:45:07 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKESFML_HPP
#define SNAKESFML_HPP

#include <NibblerException.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Snake.hpp>

class SnakeSFML {
   private:
    std::vector<TVertex> *_body;
    std::vector<TVertex> *_obstacles;
    sf::RenderWindow _display;
    sf::Clock _clock;
    float _start;
    float _now;
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

   public:
    class SnakeSFMLException : public NibblerException {
       private:
        std::string _exc;

       public:
        SnakeSFMLException(std::string);
        SnakeSFMLException(SnakeSFMLException const &);
        SnakeSFMLException &operator=(SnakeSFMLException const &);
        virtual const char *what() const throw();
    };

    SnakeSFML(int, int);

    SnakeSFML(SnakeSFML const &);
    SnakeSFML &operator=(SnakeSFML const &);
    ~SnakeSFML();

    SnakeT getSnake();
    void updateSnake(SnakeT);

    void init();
    void initObstacles();
    bool checkFood();
    void randFood();
    bool moveHead(int);
    bool checkCollusion(TVertex &);
};

extern "C" {
SnakeSFML *createSnake(int, int);
void deleteSnakeAllegro(SnakeSFML *);
}

#endif  //SNAKESFML_HPP