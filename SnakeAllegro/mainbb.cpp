
if (ev.type == ALLEGRO_EVENT_TIMER) {
    if (checkFood()) {
        randFood();
        _speed += 0.5;
        al_set_timer_speed(_timer, 1.0 / _speed);
    }
    if ((*_vertex)[0].x2 >= WINW || (*_vertex)[0].y2 >= WINH)
        break;
    else if ((*_vertex)[0].x1 <= 0 || (*_vertex)[0].y1 <= 0)
        break;

    // TVertex tmpTV;
    // TVertex tmpTV2;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    for (std::vector<TVertex>::iterator it = _vertex->begin(); it != _vertex->end(); ++it) {
        if (it == _vertex->begin()) {
            if (_key[KEY_UP]) {
                it->y1 -= 15;
                it->y2 -= 15;
            } else if (_key[KEY_DOWN]) {
                it->y1 += 15;
                it->y2 += 15;
            } else if (_key[KEY_LEFT]) {
                it->x1 -= 15;
                it->x2 -= 15;
            } else if (_key[KEY_RIGHT]) {
                it->x1 += 15;
                it->x2 += 15;
            }
            drawRect(*it, al_map_rgb(255, 0, 0));

            //  al_draw_circle
            drawRect(_food, al_map_rgb(255, 0, 255));
        }
    }
    al_flip_display();
} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
    int tmp;
    for (int i = 0; i < 4; i++) {
        if (_key[i])
            tmp = i;
    }
    std::cout << "YESSSs" << std::endl;
    switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_UP: {
            if (tmp != KEY_DOWN && tmp != KEY_UP) {
                _prevKey = tmp;
                std::fill(_key, _key + 4, false);
                _key[KEY_UP] = true;
            }
        } break;
        case ALLEGRO_KEY_DOWN: {
            if (tmp != KEY_UP && tmp != KEY_DOWN) {
                _prevKey = tmp;
                std::fill(_key, _key + 4, false);
                _key[KEY_DOWN] = true;
            }
        } break;
        case ALLEGRO_KEY_LEFT: {
            if (tmp != KEY_RIGHT && tmp != KEY_LEFT) {
                _prevKey = tmp;
                std::fill(_key, _key + 4, false);
                _key[KEY_LEFT] = true;
            }
        } break;
        case ALLEGRO_KEY_RIGHT: {
            if (tmp != KEY_LEFT && tmp != KEY_RIGHT) {
                _prevKey = tmp;
                std::fill(_key, _key + 4, false);
                _key[KEY_RIGHT] = true;
            }
        } break;
        case ALLEGRO_KEY_ESCAPE:
            _doExit = true;
            break;
    }
} else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    break;
}