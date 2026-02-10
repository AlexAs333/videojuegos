#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Crear ventana (Sintaxis SDL2: X, Y, W, H, Flags)
    SDL_Window* window = SDL_CreateWindow(
        "Proyecto SDL2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cout << "Error Ventana: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Esperar 3 segundos
    SDL_Delay(3000);

    // Limpiar
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}