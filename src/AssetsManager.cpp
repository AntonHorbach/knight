#include "AssetsManager.hpp"

sharedTexture makeSharedTexture(SDL_Texture* texture) {
    return {texture, SDL_DestroyTexture};
}

bool AssetsManager::loadTexture(const std::string& path,
                                const std::string& key)
{
    bool res = true;
    SDL_Surface* surface  = IMG_Load(path.c_str());

    if(!surface) {
        SDL_Log("IMG_Load failed: %s", SDL_GetError());
        res = false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer,
                                                        surface);
    if(res && !texture) {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        res = false;
    }

    if(res) {
        textures.insert({key, makeSharedTexture(texture)});
    }

    SDL_FreeSurface(surface);

    return res;
}

sharedTexture AssetsManager::getTexture(const std::string& key) {
    return textures[key];
}

void AssetsManager::drawTexture(const sharedTexture& texture,
                                SDL_Rect srcrect,
                                SDL_Rect dstrect)
{
    if(texture.get() != nullptr) {
        SDL_RenderCopy(Game::renderer, texture.get(), &srcrect, &dstrect);
    }
    else {
        std::cout << "Texture is not loaded" << std::endl;
    }
}

void AssetsManager::drawTexture(const std::string& key, SDL_Rect srcrect,
                        SDL_Rect dstrect)
{
    drawTexture(textures[key], srcrect, dstrect);
}