#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // 1. Inicializar el sistema de Video y Audio
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "Error SDL2: " << SDL_GetError() << std::endl;
        return -1;
    }

    // 2. Inicializar SDL_image (Cargador de PNG)
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "Error SDL_image: " << IMG_GetError() << std::endl;
        return -1;
    }

    // 3. Inicializar SDL_mixer (Audio de 44.1kHz)
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Error SDL_mixer: " << Mix_GetError() << std::endl;
        return -1;
    }

    // 4. Crear una ventana para ver que el motor "respira"
    SDL_Window* window = SDL_CreateWindow(
        "Dungeon Crawler - Smoke Test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, 0
    );

    if (!window) {
        std::cerr << "No se pudo crear la ventana: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "¡SISTEMA OPERATIVO Y FUNCIONAL!" << std::endl;
    std::cout << "SDL2, Image y Mixer cargados correctamente." << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    // Esperar 3 segundos para que puedas celebrarlo
    SDL_Delay(3000);

    // Limpieza
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}