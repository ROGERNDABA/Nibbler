/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:06:09 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/24 16:45:09 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <allegro5/allegro.h>
#include <iostream>

int main(int ac, char *av[]) {
    ALLEGRO_DISPLAY *display = NULL;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    display = al_create_display(640, 480);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));

    while (1) {
        al_flip_display();
        /* code */
    }

    // al_rest(10.0);

    al_destroy_display(display);

    return 0;
}