#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;  // Declare event separately
        while (window.pollEvent(event))  // pollEvent returns a bool, not optional
        {
            if (event.type == sf::Event::Closed)  // Correct way to check event type
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}
