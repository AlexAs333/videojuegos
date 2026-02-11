#include "GameObject.h"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y) {
    renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet, ren);
    xpos = x;
    ypos = y;
    
    updateRects();
}

GameObject::~GameObject() {
    // Texture managed by TextureManager
}

void GameObject::update() {
    // Base implementation does nothing
    // Derived classes override this
}

void GameObject::render() {
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

void GameObject::updateRects(int w, int h) {
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = w;
    srcRect.h = h;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = w;
    destRect.h = h;
}