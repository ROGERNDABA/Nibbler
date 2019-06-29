#include <SDL.h>
#include <Snake.hpp>
#include <iostream>

int main(int ac, char* av[]) {
    // (void)ac;
    // (void)av;
    //The window we'll be rendering to
    if (ac == 3) {
        SDL_Window* window = NULL;

        //The surface contained by the window
        SDL_Surface* screenSurface = NULL;
        SDL_Renderer* renderer = NULL;
        SDL_Event event;
        Uint32 start = 0, now;
        SDL_Rect rect;
        int WINW = std::stoi(av[1]);
        int WINH = std::stoi(av[2]);

        rect.x = WINW / 2;
        rect.y = WINH / 2;
        rect.w = 15;
        rect.h = 15;
        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            return -1;
        }
        //Create window
        window = SDL_CreateWindow("NIBBLER SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINW, WINH, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return -1;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        // screenSurface = SDL_GetWindowSurface(window);
        // SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
        // SDL_UpdateWindowSurface(window);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        while (1) {
            SDL_PollEvent(&event);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            now = SDL_GetTicks();
            if (now >= start + (1000 * (1.0 / 8))) {
                rect.x += 15;
                // rect.y += 15;
                // std::cout << "time :  " << (1000 * (1.0 / 20)) << std::endl;
                // std::cout << "rect x :  " << rect.x << std::endl;
                start = now;
                // break;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    break;
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderPresent(renderer);
        }
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    return 0;
}