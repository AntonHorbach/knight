#include "game.hpp"

#include "AssetsManager.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
AssetsManager Game::assetsManager;

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

    assetsManager.loadTexture("./assets/knight_anims.png", "knight");

    auto entity = entityManager.createEntity();

    entity->addComponent<Component>();
    entity->getComponent<Component>();

    vec2f vec1 = {0, 2};
    vec2f vec2 = {2, 0};

    vec1 = vec1 + vec2;
    vec2 = vec2 - vec1;

    std::cout << vec1.x << vec1.y << std::endl;
    std::cout << vec2.x << vec2.y << std::endl;

    return true;
}

void Game::draw() {
    SDL_RenderClear(renderer);

    SDL_Rect src = {0, 0, 32, 32};
    static SDL_Rect dst = {0, 0, 64, 64};
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    assetsManager.drawTexture("knight", src, dst);
    
    dst.x = (dst.x + 3) % w;
    dst.y = (dst.y + 3) % h;

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