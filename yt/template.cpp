#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace sf;
int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(800, 600), "Planetary Motion");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                window.close();
        }
        window.clear();

        window.draw();
        window.display();
    }
    return 0;
}
