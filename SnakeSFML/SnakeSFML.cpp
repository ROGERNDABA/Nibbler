/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSFML.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:16:26 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/30 19:42:31 by Roger Ndaba      ###   ########.fr       */
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
    this->randFood();
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
    _display.create(sf::VideoMode(WINW, WINH), "My window");

    while (!_doExit) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event ev;
        sf::Event prevEvent;
        _display.pollEvent(ev);

        _now = _clock.getElapsedTime().asMilliseconds();
        if (_now >= _start + (1000 * (1.0 / _speed))) {
            _display.clear(sf::Color::Black);

            if (checkFood()) {
                randFood();
                // _speed += 0.5;
                // al_set_timer_speed(_timer, 1.0 / _speed);
            }

            if (_key[KEY_UP]) {
                _doExit = moveHead(KEY_UP);
            } else if (_key[KEY_DOWN]) {
                _doExit = moveHead(KEY_DOWN);
            } else if (_key[KEY_LEFT]) {
                _doExit = moveHead(KEY_LEFT);
            } else if (_key[KEY_RIGHT]) {
                _doExit = moveHead(KEY_RIGHT);
            } else {
                _doExit = moveHead(-1);
            }
            sf::RectangleShape r;
            r.setSize(sf::Vector2f(20, 20));
            for (std::vector<TVertex>::iterator it = _vertex->begin(); it != _vertex->end(); ++it) {
                r.setPosition(it->x1, it->y1);
                if (it == _vertex->begin())
                    r.setFillColor(sf::Color::Red);
                else
                    r.setFillColor(sf::Color::White);
                _display.draw(r);
            }
            r.setPosition(_food.x1, _food.y1);
            r.setSize(sf::Vector2f(10, 10));
            r.setFillColor(sf::Color::Green);
            _display.draw(r);
            _display.display();
            _start = _now;
        } else if (ev.type == sf::Event::KeyPressed) {
            int tmp;
            for (int i = 0; i < 4; i++) {
                if (_key[i])
                    tmp = i;
            }
            switch (ev.key.code) {
                case sf::Keyboard::Up: {
                    if (tmp != KEY_DOWN && tmp != KEY_UP) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_UP] = true;
                    }
                } break;
                case sf::Keyboard::Down: {
                    if (tmp != KEY_UP && tmp != KEY_DOWN) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_DOWN] = true;
                    }
                } break;
                case sf::Keyboard::Left: {
                    if (tmp != KEY_RIGHT && tmp != KEY_LEFT) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_LEFT] = true;
                    }
                } break;
                case sf::Keyboard::Right: {
                    if (tmp != KEY_LEFT && tmp != KEY_RIGHT) {
                        _prevKey = tmp;
                        std::fill(_key, _key + 4, false);
                        _key[KEY_RIGHT] = true;
                    }
                } break;
                case sf::Keyboard::Escape:
                    _doExit = true;
                    break;
            }
            prevEvent = ev;
        } else if (ev.type == sf::Event::Closed)
            _doExit = true;
    }
}

bool SnakeSFML::checkFood() {
    TVertex tmp = (*_vertex)[0];
    if (_key[KEY_UP]) {
        if (tmp.y1 <= _food.y2 && (_food.x1 >= tmp.x1 && _food.x2 <= tmp.x2)) {
            _vertex->push_back(tmp);
            return true;
        }
    } else if (_key[KEY_DOWN]) {
        if (tmp.y2 >= _food.y1 && (_food.x1 >= tmp.x1 && _food.x2 <= tmp.x2)) {
            _vertex->push_back(tmp);
            return true;
        }
    } else if (_key[KEY_LEFT]) {
        if (tmp.x1 <= _food.x2 && (_food.y1 >= tmp.y1 && _food.y2 <= tmp.y2)) {
            _vertex->push_back(tmp);
            return true;
        }
    } else if (_key[KEY_RIGHT]) {
        if (tmp.x2 >= _food.x1 && (_food.y1 >= tmp.y1 && _food.y2 <= tmp.y2)) {
            _vertex->push_back(tmp);
            return true;
        }
    }
    return false;
}

bool SnakeSFML::moveHead(int key) {
    TVertex head = *_vertex->begin();
    TVertex tail = head;
    switch (key) {
        case 0: {
            _vertex->pop_back();
            tail.y1 = head.y1 - 20;
            tail.y2 = head.y2 - 20;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        case 1: {
            _vertex->pop_back();
            tail.y1 = head.y1 + 20;
            tail.y2 = head.y2 + 20;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        case 2: {
            _vertex->pop_back();
            tail.x1 = head.x1 - 20;
            tail.x2 = head.x2 - 20;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        case 3: {
            _vertex->pop_back();
            tail.x1 = head.x1 + 20;
            tail.x2 = head.x2 + 20;
            _vertex->insert(_vertex->begin(), tail);
        } break;
        default: {
            _vertex->pop_back();
            tail.x1 = head.x1 + 20;
            tail.x2 = head.x2 + 20;
            _vertex->insert(_vertex->begin(), tail);
        } break;
    }
    return (checkCollusion(tail)) ? true : false;
}

bool SnakeSFML::checkCollusion(TVertex& tv) {
    for (std::vector<TVertex>::iterator it = _vertex->begin() + 1; it != _vertex->end(); ++it) {
        if (tv.x1 == it->x1 && tv.x2 == it->x2 && tv.y1 == it->y1 && tv.y2 == it->y2) {
            return true;
        }
    }
    if (tv.x1 <= 0 || tv.x2 >= WINW || tv.y1 <= 0 || tv.y2 >= WINH)
        return true;
    return false;
}

void SnakeSFML::randFood() {
    _food.x1 = ((std::rand() % (WINW - 30) + 1));
    _food.x2 = _food.x1 + 5;
    _food.y1 = ((std::rand() % (WINH - 30) + 1));
    _food.y2 = _food.y1 + 5;
}