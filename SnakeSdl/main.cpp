#include <SDL.h>
#include <iostream>

int main(int ac, char* av[]) {
    (void)ac;
    (void)av;
    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;
    SDL_Event event;
    Uint32 start = 0;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    //Create window
    window = SDL_CreateWindow("NIBBLER SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
    SDL_UpdateWindowSurface(window);

    start = SDL_GetTicks();
    while (1) {
        SDL_WaitEvent(&event);
        if (SDL_GetTicks() - start > 500) {
            std::cout << "yes" << std::endl;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP)
                    break;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}