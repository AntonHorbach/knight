#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include <SDL2/SDL.h>

class Game {
    SDL_Window* window;
    bool running;

    void draw();
    void handleEvents();
    void update();

public:
    Game() = default;

    static SDL_Renderer* renderer;
    static SDL_Event event;

    bool init(const char* title, size_t width, size_t height, bool fullscreen);
    int exec();

    ~Game();
};
#endif