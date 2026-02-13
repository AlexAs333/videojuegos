#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>

class InputHandler {
public:
    // Actualiza el mapa de teclas (se llama en cada frame)
    static void Update();

    // Consulta si una tecla espec�fica est� pulsada
    static bool IsKeyDown(SDL_Scancode key);

    // Consulta si una tecla se acaba de pulsar (transición)
    static bool IsKeyPressed(SDL_Scancode key);

private:
    // Puntero al array interno de SDL que guarda el estado del teclado
    //static const Uint8* keyboardState;

    static Uint8 currentKeyboardState[SDL_NUM_SCANCODES];
    static Uint8 prevKeyboardState[SDL_NUM_SCANCODES];
};

#endif
