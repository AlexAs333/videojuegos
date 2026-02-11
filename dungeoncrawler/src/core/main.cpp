#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game();

    // Arrancamos el motor
    if (!game->init("Dungeon Crawler Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false)) {
        return -1;
    }

    
    // El Bucle de Juego (Game Loop)
    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
    return 0;
}