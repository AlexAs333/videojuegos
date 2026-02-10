#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class TextureManager {
public:
    // Carga una imagen y la devuelve como textura de GPU
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);

    // Dibuja la textura en pantalla
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* ren);
};

#endif#pragma once
