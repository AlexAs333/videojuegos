#include "Game.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include <SDL2/SDL_image.h>
#include "../systems/ai/EnemyAI.h"

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr), player(nullptr), enemy(nullptr) {}
Game::~Game() {}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

    // Inicializamos TODO (Video y Audio)
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        // Creamos el renderer: el encargado de hablar con la tarjeta gr�fica
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer) {
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                std::cout << "Error SDL_image: " << IMG_GetError() << std::endl;
            }

            // Declare AI before creating enemy to avoid circular dependency
            EnemyAI* basicAI = new EnemyAI(200.0f, 300.0f, 0.3f); // detection, aggro, fleeHP
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            player = new Player("assets/human.png", renderer, 100, 100);
            enemy = new Enemy("Goblin", "assets/goblin.png", renderer, 400, 300, basicAI);

            lastTime = SDL_GetTicks();
            deltaTime = 0.0f;
            
            isRunning = true;
        }
        else {
            return false; // Si no hay renderer, el motor NO ha arrancado bien
        }
    }
    else {
        return false;
    }
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // Usamos un while para vaciar todos los eventos
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }

    // Actualizamos el estado del teclado despu�s de procesar los eventos
    InputHandler::Update();
}

void Game::update() {
    // Calculate delta time
    Uint32 currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
    lastTime = currentTime;

    // cap delta time to avoid big jumps
    if (deltaTime > 0.05f) deltaTime = 0.05f;

    // Update player and enemy
    player->update(deltaTime);
    enemy->update(deltaTime, player);

    // player attack with SPACE
    if (InputHandler::IsKeyDown(SDL_SCANCODE_SPACE)) {
        player->attack(enemy);
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fondo negro

    SDL_RenderClear(renderer);

    player->render(); 
    enemy->render();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    delete player; 
    delete enemy;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Motor cerrado correctamente." << std::endl;
}