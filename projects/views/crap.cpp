#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <regex>

using namespace sf;
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fixed Background Example");
    window.setFramerateLimit(60);

    // Load the background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("mountain.jpg")) {
        return -1; // Handle error
    }

    // Create a sprite for the background
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y
    );


    RectangleShape rect;
    rect.setFillColor(Color::White);
    rect.setSize(Vector2f(50.f,50.f));

    View view(sf::FloatRect(0,0,400,300));
    view.setCenter(200,150);
        Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    view.zoom(0.9f); // Zoom in
                else
                    view.zoom(1.1f); // Zoom out
            }
        }
        float dt = clock.restart().asSeconds();

        window.clear();

        window.draw(backgroundSprite);

        if(Keyboard::isKeyPressed(Keyboard::Key::H))
        {
            rect.move(-5.f*dt*60,0.f);
        }

        if(Keyboard::isKeyPressed(Keyboard::Key::J))
        {
            rect.move(0.f,5.f*dt*60);
        }

        if(Keyboard::isKeyPressed(Keyboard::Key::K))
        {
            rect.move(0.f,-5.f*dt*60);
        }

        if(Keyboard::isKeyPressed(Keyboard::Key::L))
        {
            rect.move(5.f*dt*60,0.f);
        }
        window.draw(rect);
        window.display();
    }

    return 0;
}

