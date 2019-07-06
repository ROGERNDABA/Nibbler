/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSFML.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:13:31 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/06 17:07:48 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKESFML_HPP
#define SNAKESFML_HPP

#include <NibblerException.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Snake.hpp>

class SnakeSFML : public Snake {
   private:
    std::vector<TVertex> *_body;
    std::vector<TVertex> *_obstacles;
    sf::RenderWindow _display;
    sf::Clock _clock;
    sf::Music _beep;
    sf::Music _buzz;
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
    int _softExit;

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

    SnakeT getSnake() const;
    int getEvent() const;
    void updateSnake(SnakeT);
    void stop();

    void init();
    void initObstacles();
    bool checkFood();
    void randFood();
    bool moveHead(int);
    bool checkCollusion(TVertex &);
    void gameOver();
};

extern "C" {
SnakeSFML *createSnake(int, int);
void deleteSnake(SnakeSFML *);
}

#endif  //SNAKESFML_HPP