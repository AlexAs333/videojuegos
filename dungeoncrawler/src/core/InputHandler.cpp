#include "InputHandler.h"
#include <cstring>

// Inicializamos los arrays a 0
Uint8 InputHandler::currentKeyboardState[SDL_NUM_SCANCODES] = {0};
Uint8 InputHandler::prevKeyboardState[SDL_NUM_SCANCODES] = {0};

void InputHandler::Update() {
    // Guardar estado anterior
    memcpy(prevKeyboardState, currentKeyboardState, SDL_NUM_SCANCODES);
    
    // SDL_GetKeyboardState devuelve un puntero a una tabla interna 
    // que se actualiza automáticamente cada vez que llamamos a SDL_PollEvent
    // Lo copiamos a nuestro propio array
    const Uint8* sdlState = SDL_GetKeyboardState(nullptr);
    memcpy(currentKeyboardState, sdlState, SDL_NUM_SCANCODES);
}

bool InputHandler::IsKeyDown(SDL_Scancode key) {
    // Si el valor en esa posición es 1, la tecla está pulsada
    return currentKeyboardState[key] == 1;
}

bool InputHandler::IsKeyPressed(SDL_Scancode key) {
    // Tecla pulsada = está pulsada AHORA pero NO estaba antes
    return currentKeyboardState[key] == 1 && prevKeyboardState[key] == 0;
}