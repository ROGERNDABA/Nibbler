/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSFML.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:13:31 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/03 15:45:43 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKESFML_HPP
#define SNAKESFML_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Snake.hpp>

class SnakeSFML {
   private:
    std::vector<TVertex> *_body;
    std::vector<TVertex> *_obstacles;
    sf::RenderWindow _display;
    // SDL_Renderer *_renderer;
    // SDL_Event _event;
    sf::Clock _clock;
    float _start;
    float _now;
    TVertex _food;
    int WINW;
    int WINH;

    bool *_key;
    int _prevKey;
    bool _doExit;
    float _speed;
    int _score;

   public:
    class SnakeSFMLException : std::exception {
       private:
        std::string _exc;

       public:
        SnakeSFMLException(std::string);
        SnakeSFMLException(SnakeSFMLException const &);
        SnakeSFMLException &operator=(SnakeSFMLException const &);
        virtual const char *what() const throw();
    };

    SnakeSFML(int, int);
    SnakeSFML(SnakeT);

    SnakeSFML(SnakeSFML const &);
    SnakeSFML &operator=(SnakeSFML const &);
    ~SnakeSFML();

    void init();
    void initObstacles();
    // void drawRect(TVertex &, ALLEGRO_COLOR);
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