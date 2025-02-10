#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Selection Sort Visualization");

    sf::CircleShape shape(50.f);
shape.setFillColor(sf::Color::Black);
shape.setPosition(100,100);
shape.setOutlineThickness(2.f);
shape.setOutlineColor(sf::Color(250, 150, 100));
    sf::Vector2f velocity(1.f,-1.f);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2f position = shape.getPosition();
        if(position.x >=500)
        {
            shape.setPosition(0,position.y);
        }
        if(position.x+2*shape.getRadius()<=0.0)
        {
            shape.setPosition(500,position.y);
        }
        if(position.y >=500)
        {
            shape.setPosition(position.x,0);
        }
        if(position.y+2*shape.getRadius()<=0.0)
        {
            shape.setPosition(position.x,500);
        }
        shape.move(velocity);
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}

