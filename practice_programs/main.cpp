#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <iostream>
#include <vector>
using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Thick Line",sf::Style::Resize|sf::Style::Close);
sf::ContextSettings settings;
settings.antialiasingLevel = 8;
RectangleShape rect;
    rect.setSize(Vector2f(50.f,50.f));
    rect.setPosition(100.f,100.f);
    sf::View view;
view.reset(sf::FloatRect({200.f, 200.f}, {300.f, 200.f}));
    view.setRotation(44);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(rect);
        window.display();
    }
    return 0;
}
