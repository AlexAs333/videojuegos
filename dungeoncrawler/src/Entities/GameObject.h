/*
 * Class GameObject, base class for all entities in the game that have a position and can be rendered.
 * Contains basic attributes like position, texture, and methods for updating and rendering.
 * Character will derive from this class to add specific behavior and attributes related to D&D mechanics. 
 */
#pragma once

#include <SDL2/SDL.h>
#include "../core/TextureManager.h"

// He hecho la clase más genérica para que Character pueda heredar
class GameObject {
protected: 
    SDL_Renderer* renderer;
    SDL_Texture* objTexture;

    int xpos, ypos;

    SDL_Rect srcRect, destRect;
public:
    GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
    ~GameObject();

    virtual void update();
    virtual void render();

    // getters
    int getX() const { return xpos; }
    int getY() const { return ypos; }
    SDL_Rect getDestRect() const { return destRect; }

protected: 
    void updateRects(int w = 64, int h = 64);
};

