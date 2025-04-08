#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>
#include <cmath>
using namespace sf;

int main() {
    RenderWindow window(VideoMode(800,600), "Bacteria World");
    window.setFramerateLimit(60);

    sf::Texture background;
    if(!background.loadFromFile("bacteria.jpg"))
        return -1;

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(background);

backgroundSprite.setScale(
    float(window.getSize().x) / background.getSize().x,
    float(window.getSize().y) / background.getSize().y
);

    sf::View view;
    /*view.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));*/
    view.setSize(400.f,300.f);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) view.move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) view.move(0, 5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) view.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) view.move(5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) view.zoom(0.9f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) view.zoom(1.1f);
        window.clear();
        window.draw(backgroundSprite);
        window.setView(view);
        /*window.setView(window.getDefaultView());*/
        window.display();
    }
    return 0;
}

