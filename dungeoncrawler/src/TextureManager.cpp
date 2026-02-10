#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* ren) {
    // 1. Cargamos la imagen en una "Surface" (memoria RAM)
    SDL_Surface* tempSurface = IMG_Load(fileName);
    if (tempSurface == nullptr) {
        std::cout << "ERROR: No se encuentra la imagen en: " << fileName
            << " | Motivo: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // 2. Pasamos la información de la RAM a la GPU (Texture)
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);

    // 3. ¡Importante! Liberamos la Surface porque ya no la necesitamos
    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* ren) {
    // Copia la textura del buffer trasero al renderer
    SDL_RenderCopy(ren, tex, &src, &dest);
}