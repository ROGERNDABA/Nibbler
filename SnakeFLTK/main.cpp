/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:33:24 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/15 13:13:35 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
// #include <FL/fl_draw.H>
#include <iostream>

int main() {
    Fl_Window *window = new Fl_Window(900, 600);
    window->position(0, 0);
    window->color(FL_BLACK);
    while (1) {
        int ev = Fl::event();
        if (ev == FL_SHORTCUT) {
            if (Fl::event_key() == FL_Escape)
                break;
        }
        for (int i = 0; i < 3; ++i) {
            Fl_Box *box = new Fl_Box(20, 40 + i * 120, 300, 100, "Hello, World!");
            box->box(FL_UP_BOX);
            box->labelfont(FL_BOLD + FL_ITALIC);
            box->labelsize(36);
            box->labeltype(FL_SHADOW_LABEL);
        }
        window->end();
        window->show();
        // fl_push_clip(200, 200, 15, 15);
        Fl::check();
    }
    delete window;
}
