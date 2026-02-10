#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include <SDL2/SDL_image.h>

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

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            player = new GameObject("../assets/goblin.png", renderer, 100, 100);
            enemy = new GameObject("../assets/goblin.png", renderer, 200, 200);

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
    player->Update(); // El objeto recalcula sus rect�ngulos internos
    enemy->Update();
}

void Game::render() {
    SDL_RenderClear(renderer);

    player->Render(); // El objeto se dibuja solo
    enemy->Render();

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