#include "game.hpp"

#include "AssetsManager.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
AssetsManager Game::assetsManager;

static shEntity player = {};

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

    player = entityManager.createEntity();
    player->addComponent<TransformComponent>(vec2f{300, 300}, vec2f{10, 10});
    player->addComponent<SpriteComponent>(SDL_Rect{0, 0, 32, 32}, SDL_Rect{0, 0, 64, 64}, "knight");
    player->addComponent<JumperComponent>(200.f);
    player->addComponent<KeybordInput>();

    systems.push_back(std::unique_ptr<System>{new MovementSystem(&entityManager)});
    systems.push_back(std::unique_ptr<System>{new DrawSystem(&entityManager)});
    systems.push_back(std::unique_ptr<System>(new JumpSystem(&entityManager)));

    return true;
}

void Game::draw() {
    SDL_RenderClear(renderer);

    for(auto& sys : systems) {
        sys->draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
    SDL_PollEvent(&event);

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

void Game::update() {
    for(auto& sys : systems) {
        sys->update();
    }
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