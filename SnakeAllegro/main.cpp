/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:06:09 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/25 11:43:01 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_primitives.h>
#include <Snake.hpp>
#include <iostream>

enum E_KEYS {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT
};

int main(int ac, char *av[]) {
    (void)av;
    (void)ac;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    float x1 = WINW / 2;
    float y1 = WINH / 2;
    float x2 = x1 + 30;
    float y2 = y1 + 30;
    bool key[4] = {false, false, false, false};

    if (!al_init()) {
        std::cerr << "Couldn't init allegro" << std::endl;
        return -1;
    }
    if (!al_install_keyboard()) {
        std::cerr << "failed to initialize the keyboard!" << std::endl;
        return -1;
    }
    display = al_create_display(WINW, WINH);
    if (!display) {
        std::cerr << "Couldn't init display" << std::endl;
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        return -1;
    }

    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    while (1) {
        ALLEGRO_EVENT ev;
        al_get_next_event(event_queue, &ev);
        if (key[KEY_UP]) {
            y1 -= 6;
            y2 -= 6;
        }
        if (key[KEY_DOWN]) {
            y1 += 6;
            y2 += 6;
        }
        if (key[KEY_LEFT]) {
            x1 -= 6;
            x2 -= 6;
        }
        if (key[KEY_RIGHT]) {
            x1 += 6;
            x2 += 6;
        }
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;

                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;

                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;
            }
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        // al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 255, 255));
        al_flip_display();
    }

    // al_rest(10.0);

    al_destroy_display(display);

    return 0;
}