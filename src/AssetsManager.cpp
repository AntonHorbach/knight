#include "AssetsManager.hpp"

void destroyTexture(Texture* texture) {
    SDL_DestroyTexture(texture->texture);
    delete texture;
}

sharedTexture makeSharedTexture(Texture* texture) {
    return {texture, destroyTexture};
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

    Texture* texture = new Texture {
        SDL_CreateTextureFromSurface(Game::renderer, surface),
        surface->w, surface->h
    };
    
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
                                SDL_Rect dstrect,
                                SDL_RendererFlip flip)
{
    if(texture.get() != nullptr) {
        SDL_RenderCopyEx(Game::renderer, texture.get()->texture,
                        &srcrect, &dstrect,
                        0.0, nullptr, flip);
    }
    else {
        SDL_Log("Can't draw texture: not loaded");
    }
}

void AssetsManager::drawTexture(const std::string& key, SDL_Rect srcrect,
                        SDL_Rect dstrect, SDL_RendererFlip flip)
{
    sharedTexture texture = nullptr;

    if(textures.find(key) != textures.end()) {
        texture = textures[key];
    }

    drawTexture(std::move(texture), srcrect, dstrect, flip);
}