#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "../entities/Character.h"
#include <iostream>

class Player; // Forward declaration
class Enemy; // Forward declaration

class Game {
public:
    Game();
    ~Game();

    // Inicializa SDL, la ventana y el renderizador
    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents(); // Escucha teclado/rat�n
    void update();       // L�gica del juego (IA, f�sica)
    void render();       // Dibuja en pantalla
    void clean();        // Libera memoria al salir

    bool running() { return isRunning; }

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer; // El "pincel" que dibuja todo

    Player* player;
    Enemy* enemy;
    GameObject* background;

    // Timing
    Uint32 lastTime;
    float deltaTime;

};

#endif