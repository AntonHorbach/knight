#include "game.hpp"

#include "AssetsManager.hpp"

template <typename Struct, typename Collection>
bool loadStructFromFile(Collection&, const std::string&);

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


    auto player = manager.createEntity();
    player->addComponent<TransformComponent>(vec2f{500, 300}, vec2f{10, 10});
    player->addComponent<SpriteComponent>(SDL_Rect{0, 0, 50, 37}, SDL_Rect{0, 0, 100, 74}, "knight",
                                            true);
    player->addComponent<JumperComponent>(200.f);
    player->addComponent<KeyboardInput>();
    player->addComponent<ColliderComponent>(SDL_Rect{28, 14, 36, 58});
    player->addComponent<HealthComponent>();
    player->addComponent<AttackComponent>();


    auto enemy = manager.createEntity();
    enemy->addComponent<TransformComponent>(vec2f{400, 300}, vec2f{10, 10});
    enemy->addComponent<SpriteComponent>(SDL_Rect{0, 0, 50, 39}, SDL_Rect{0, 0, 100, 78}, "knight");
    enemy->addComponent<ColliderComponent>(SDL_Rect{28, 14, 36, 58});
    enemy->addComponent<HealthComponent>();

    if(!loadStructFromFile<Animation>(
            player->getComponent<SpriteComponent>().animations,
            "./assets/playerAnimations.anms"
        ))
    {
        SDL_Log("Failed to load animations");
        return false;
    }

    if(!loadStructFromFile<Attack>(
            player->getComponent<AttackComponent>().attacks,
            "./assets/playerAttacks.atcks"
    ))
    {
        SDL_Log("Failed to load attacks");
        return false;
    }


    manager.addSystem<KeyboardSystem>();
    manager.addSystem<MovementSystem>();
    manager.addSystem<JumpSystem>();
    manager.addSystem<AttackSystem>();
    manager.addSystem<CollisionSystem>();
    manager.addSystem<AnimationSystem>();
    manager.addSystem<HealthSystem>();
    manager.addSystem<DrawSystem>();

    return true;
}

void Game::draw() {
    SDL_RenderClear(renderer);

    manager.draw();

    SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
    if(eventBuffer.pollEvent(&event)) {
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
    eventBuffer.update();
    manager.update();
}

int Game::exec() {
    const Uint32 fps = 30;
    const Uint32 frame_delay = 1000 / fps;

    while(running) {
        Uint32 frame_start = SDL_GetTicks();

        draw();
        handleEvents();
        update();

        Uint32 frame_time = SDL_GetTicks() - frame_start;

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

template <typename Struct, typename Collection>
bool loadStructFromFile(Collection& col, const std::string& fileName) {
    std::ifstream file(fileName);

    if(!file) {
        return false;
    }

    Struct obj{};
    while(!file.eof()) {
        if(!(file >> obj)) {
            return false;
        }

        insert(col, std::move(obj));
    }

    return true;
}