#include <SFML/Graphics.hpp>

int main() {
    // CAMBIO 1: SFML 3 usa llaves {} para definir tamaños (Vector2u)
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Proyecto Universal (SFML 3)");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Cyan);
    
    // CAMBIO 2: Para posiciones también se usan llaves {} (Vector2f)
    shape.setPosition({300.f, 200.f});

    while (window.isOpen()) {
        // CAMBIO 3: El manejo de eventos ha cambiado totalmente.
        // Ahora pollEvent() no pide parámetros y devuelve un opcional.
        while (const std::optional event = window.pollEvent()) {
            
            // CAMBIO 4: Para cerrar, se verifica si el evento es del tipo Closed
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}