#include "game.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::init(const char* title, size_t width, size_t height,
                bool fullscreen)
{
    SDL_DisplayMode mode;
    uint32_t window_flags = (fullscreen
                            ? SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN
                            : SDL_WINDOW_SHOWN);

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    if(SDL_GetDisplayMode(0, 0, &mode) != 0) {
        SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
        return false;
    }

    size_t w, h;
    if(!fullscreen) {
        w = width;
        h = height;
    }
    else {
        w = mode.w;
        h = mode.h;
    }

    window = SDL_CreateWindow(title,
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        w, h, window_flags);
    if(window == nullptr) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255);

    running = true;

    return true;
}

void Game::draw() {
    SDL_RenderClear(renderer);
    
    SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if(SDLK_ESCAPE == event.key.keysym.sym)
                    running = false;
                break;
            default:
                break;
        }
    }
}

void Game::update() {

}

int Game::exec() {
    const size_t fps = 30;
    const size_t frame_delay = 1000 / fps;

    while(running) {
        Uint32 frame_start = SDL_GetTicks();

        draw();
        handleEvents();
        update();

        int frame_time = SDL_GetTicks() - frame_start;

        if(frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
    }

    return 0;
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}