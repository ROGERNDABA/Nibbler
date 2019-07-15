/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:33:24 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/15 11:45:21 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_draw.H>
#include <iostream>

int main() {
    Fl_Window *window = new Fl_Window(340, 180);
    window->end();
    window->show();
    while (1) {
        Fl::event();
    }
}
