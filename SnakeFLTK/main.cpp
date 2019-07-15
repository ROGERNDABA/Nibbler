/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:33:24 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/15 11:54:19 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
// #include <FL/Fl_draw.H>
#include <iostream>

int main() {
    Fl_Window *window = new Fl_Window(900, 600);
    // window->color(0, 0, 0);
    window->end();
    window->show();
    while (1) {
        int ev = Fl::event();
        if (ev == FL_SHORTCUT) {
            if (Fl::event_key() == FL_Escape)
                break;
        }
        Fl::check();
    }
}
