#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Paint App");
    
    std::vector<sf::CircleShape> circles;  
    sf::Color currentColor = sf::Color::Black;  // Default color

    std::vector<sf::Vertex> lines;
    bool drawing = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Change color on keypress
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) currentColor = sf::Color::Red;
                if (event.key.code == sf::Keyboard::G) currentColor = sf::Color::Green;
                if (event.key.code == sf::Keyboard::B) currentColor = sf::Color::Blue;
                if (event.key.code == sf::Keyboard::Y) currentColor = sf::Color::Yellow;
                if (event.key.code == sf::Keyboard::K) currentColor = sf::Color::Black;
            }
            /*if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {*/
            /*    lines.push_back(sf::Vertex(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), currentColor));*/
            /*    drawing = true;*/
            /*}*/
            /**/
            /*if (event.type == sf::Event::MouseMoved && drawing) {*/
            /*    lines.push_back(sf::Vertex(sf::Vector2f(event.mouseMove.x, event.mouseMove.y), currentColor));*/
            /*}*/
            /**/
            /*if (event.type == sf::Event::MouseButtonReleased)*/
            /*    drawing = false;*/
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::CircleShape dot(3.f);
            dot.setFillColor(currentColor);
            dot.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            circles.push_back(dot);
        }

        window.clear(sf::Color::White);

        for (auto& circle : circles)
            window.draw(circle);
        /*if(!lines.empty())*/
        /*    window.draw(lines.data(),lines.size(),sf::LinesStrip);*/
        window.display();
        }
    return 0;
    }
