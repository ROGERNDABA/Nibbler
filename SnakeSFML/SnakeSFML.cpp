/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSFML.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:16:26 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/30 18:35:52 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeSFML.hpp"

SnakeSFML::SnakeSFML(int w, int h)
    : WINW(w), WINH(h), _prevKey(3), _doExit(false), _speed(8), _start(0) {
    TVertex tv;

    tv.x1 = (WINW / 2);
    tv.y1 = (WINH / 2);
    tv.x2 = tv.x1 + 20;
    tv.y2 = tv.y1 + 20;
    std::vector<TVertex>* tvt = new std::vector<TVertex>;
    tvt->push_back(tv);
    this->_key = new bool[4];
    std::fill(_key, _key + 4, false);
    _key[3] = true;
    this->_vertex = tvt;
    // this->randFood();
    this->init();
}

SnakeSFML::SnakeSFML(std::vector<TVertex>& vertex) : _vertex(&vertex) {}

SnakeSFML::SnakeSFMLException::SnakeSFMLException(std::string exc) {
    this->_exc = "\033[31m" + exc + "\033[0m";
}

SnakeSFML::SnakeSFMLException::SnakeSFMLException(SnakeSFML::SnakeSFMLException const& copy) {
    *this = copy;
}

const char* SnakeSFML::SnakeSFMLException::what() const throw() {
    return _exc.c_str();
}

SnakeSFML::SnakeSFMLException& SnakeSFML::SnakeSFMLException::operator=(SnakeSFML::SnakeSFMLException const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

SnakeSFML::~SnakeSFML() {
    _display.close();
}

SnakeSFML::SnakeSFML(SnakeSFML const& copy) {
    *this = copy;
};

SnakeSFML& SnakeSFML::operator=(SnakeSFML const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

void SnakeSFML::init() {
    _display.create(sf::VideoMode(900, 600), "My window");

    while (!_doExit) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event ev;
        _display.pollEvent(ev);

        _now = _clock.getElapsedTime().asMilliseconds();
        if (_now >= _start + (1000 * (1.0 / 8))) {
            _display.clear(sf::Color::Black);
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(100, 50));
            rectangle.setPosition(10, 20);
            _display.draw(rectangle);
            _display.display();
            _start = _now;
        } else if (ev.type == sf::Event::KeyPressed) {
            switch (ev.key.code) {
                case sf::Keyboard::Left:
                    std::cout << "-----> yes" << std::endl;
                    break;
                case sf::Keyboard::Escape:
                    _doExit = true;
            }
        } else if (ev.type == sf::Event::Closed)
            _doExit = true;
    }
}