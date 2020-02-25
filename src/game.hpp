#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <memory>

#include "ECS/Components.hpp"
#include "ECS/Systems.hpp"

class AssetsManager;

class Game {
    SDL_Window* window;
    Manager entityManager;
    std::vector<std::unique_ptr<System>> systems; 

    bool running;

    void draw();
    void handleEvents();
    void update();

public:
    Game() = default;

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static AssetsManager assetsManager;

    bool init(const char* title, size_t width, size_t height,
                bool fullscreen);
    int exec();

    ~Game();
};
#endif