#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "GameObject.h"
#include <iostream>


class Game {
public:
    Game();
    ~Game();

    // Inicializa SDL, la ventana y el renderizador
    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents(); // Escucha teclado/ratón
    void update();       // Lógica del juego (IA, física)
    void render();       // Dibuja en pantalla
    void clean();        // Libera memoria al salir

    bool running() { return isRunning; }

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer; // El "pincel" que dibuja todo

    GameObject* player;
    GameObject* enemy;

};

#endif