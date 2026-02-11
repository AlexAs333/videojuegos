#include "InputHandler.h"


// Inicializamos el puntero a null
const Uint8* InputHandler::keyboardState = nullptr;

void InputHandler::Update() {
    // SDL_GetKeyboardState devuelve un puntero a una tabla interna 
    // que se actualiza autom�ticamente cada vez que llamamos a SDL_PollEvent
    keyboardState = SDL_GetKeyboardState(nullptr);
}

bool InputHandler::IsKeyDown(SDL_Scancode key) {
    if (keyboardState != nullptr) {
        // Si el valor en esa posici�n es 1, la tecla est� pulsada
        return keyboardState[key] == 1;
    }
    return false;
}