/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeAllegro.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 12:37:43 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/25 15:10:34 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeAllegro.hpp"

SnakeAllegro::SnakeAllegro(TVertex vt) {
    std::vector<TVertex>* tvt = new std::vector<TVertex>;
    tvt->push_back(vt);
    this->_vertex = tvt;
    this->randFood();
    randFood();
    this->init();
}

SnakeAllegro::SnakeAllegro(std::vector<TVertex>& vertex) : _vertex(&vertex) {}

SnakeAllegro::SnakeAllegroException::SnakeAllegroException(std::string exc) {
    this->_exc = "\033[31m" + exc + "\0330m";
}

SnakeAllegro::SnakeAllegroException::SnakeAllegroException(SnakeAllegro::SnakeAllegroException const& copy) {
    *this = copy;
}

const char* SnakeAllegro::SnakeAllegroException::what() const throw() {
    return (this->_exc.c_str());
}

SnakeAllegro::SnakeAllegroException& SnakeAllegro::SnakeAllegroException::operator=(SnakeAllegro::SnakeAllegroException const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

SnakeAllegro::~SnakeAllegro() {
    al_destroy_timer(_timer);
    al_destroy_display(_display);
    al_destroy_event_queue(_eQueue);
    std::cout << "GG" << std::endl;
}

SnakeAllegro::SnakeAllegro(SnakeAllegro const& copy) {
    *this = copy;
};

SnakeAllegro& SnakeAllegro::operator=(SnakeAllegro const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}

void SnakeAllegro::init() {
    if (!al_init()) {
        throw SnakeAllegroException("Couldn't create window");
    }
    _timer = al_create_timer(1.0 / 40);
    if (!_timer) {
        al_destroy_display(_display);
        al_destroy_timer(_timer);
        throw SnakeAllegroException("Couldn't init timer");
    }
    if (!al_install_keyboard()) {
        al_destroy_timer(_timer);
        throw SnakeAllegroException("failed to initialize the keyboard!");
    }
    _display = al_create_display(WINW, WINH);
    if (!_display) {
        al_destroy_timer(_timer);
        throw SnakeAllegroException("Couldn't init display");
    }

    _eQueue = al_create_event_queue();
    if (!_eQueue) {
        al_destroy_display(_display);
        al_destroy_timer(_timer);
        throw SnakeAllegroException("failed to create event_queue!");
    }
    al_register_event_source(_eQueue, al_get_display_event_source(_display));
    al_register_event_source(_eQueue, al_get_keyboard_event_source());
    al_register_event_source(_eQueue, al_get_timer_event_source(_timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(_timer);

    while (1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(_eQueue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if ((*_vertex)[0].x2 >= WINW || (*_vertex)[0].y2 >= WINH)
                break;
            else if ((*_vertex)[0].x1 <= 0 || (*_vertex)[0].y1 <= 0)
                break;
            for (std::vector<TVertex>::iterator it = _vertex->begin(); it != _vertex->end(); ++it) {
                std::cout << _food.x1 << std::endl;
                std::cout << _food.y1 << std::endl;
                std::cout << _food.x2 << std::endl;
                std::cout << _food.y2 << std::endl;

                it->x1 += 3;
                it->x2 += 3;
                al_clear_to_color(al_map_rgb(0, 0, 0));
                drawRect(*it, al_map_rgb(255, 0, 0));
                drawRect(_food, al_map_rgb(255, 0, 255));
                al_flip_display();
            }
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        // break;
    }
}

void SnakeAllegro::randFood() {
    _food.x1 = 0 + (std::rand() % (WINW - 30) + 1);
    _food.x2 = _food.x1 + 30;
    _food.y1 = 0 + (std::rand() % (WINH - 30) + 1);
    _food.y2 = _food.y1 + 30;
}

void SnakeAllegro::drawRect(TVertex& tv, ALLEGRO_COLOR alC) {
    al_draw_filled_rectangle(tv.x1, tv.y1, tv.x2, tv.y2, alC);
}