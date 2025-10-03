#include <stdlib.h>
#include <stdbool.h>

#include "SDL3/SDL.h"

#define SCREEN_WIDTH 1920.f
#define SCREEN_HEIGHT 1080.f
#define SCREEN_TITLE "sdl template"

#define TARGET_FPS 60

#define RECT_WIDTH 600.f
#define RECT_HEIGHT 300.f

int main(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("video init error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        SDL_Log("window init error: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0);
    if (!renderer) {
        SDL_Log("renderer init error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    const SDL_FRect rect = {
        .x = (SCREEN_WIDTH - RECT_WIDTH) * 0.5f, .y = (SCREEN_HEIGHT - RECT_HEIGHT) * 0.5f,
        .w = RECT_WIDTH, .h = RECT_HEIGHT
    };

    SDL_Event event;
    SDL_zero(event);

    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    quit = true;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_ESCAPE) {
                        quit = true;
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / TARGET_FPS);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}