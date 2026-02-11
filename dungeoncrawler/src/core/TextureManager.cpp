#include "TextureManager.h"
#include <iostream>  // Añade esto

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* ren) {
    SDL_Surface* tempSurface = IMG_Load(fileName);
    if (tempSurface == nullptr) {
        std::cout << "ERROR: No se encuentra la imagen en: " << fileName
            << " | Motivo: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    
    std::cout << "OK: Imagen cargada: " << fileName << std::endl;  // ← AÑADE ESTO

    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    
    if (tex == nullptr) {  
        std::cout << "ERROR: No se pudo crear textura: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(tempSurface);

    return tex;
}