#include "GameObject.h"
#include "TextureManager.h"
#include "InputHandler.h" 

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y) {
    renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet, ren);
    xpos = x;
    ypos = y;
}

GameObject::~GameObject() {
}

void GameObject::Update() {
    // PASO 2: La lógica de movimiento ahora vive aquí
    int speed = 2;

    if (InputHandler::IsKeyDown(SDL_SCANCODE_W)) ypos -= speed;
    if (InputHandler::IsKeyDown(SDL_SCANCODE_S)) ypos += speed;
    if (InputHandler::IsKeyDown(SDL_SCANCODE_A)) xpos -= speed;
    if (InputHandler::IsKeyDown(SDL_SCANCODE_D)) xpos += speed;

    // PASO 3: Actualizar el recorte (64x64) y la posición de destino
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 64;
    srcRect.h = 64;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 64;
    destRect.h = 64;
}

void GameObject::Render() {
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}