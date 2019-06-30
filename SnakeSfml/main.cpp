/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 15:34:54 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/30 17:39:14 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main(int ac, char *av[]) {
    (void)ac;
    (void)av;

    sf::Window window;
    window.create(sf::VideoMode(900, 600), "My window");

    // run the program as long as the window is open
    while (1) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        window.pollEvent(event);
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            break;
    }
    window.close();
    return 0;
}
