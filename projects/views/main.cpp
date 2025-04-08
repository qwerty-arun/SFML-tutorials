#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Mouse.hpp>
#include <ctime>
#include <sched.h>

int main() {

    //Init game
    float gridSizeF = 100.f; //Only one grid size value in the game, if this changges
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    float dt = 0.f;
    sf::Clock clock;
    sf::Vector2i mousePosScreen = sf::Mouse::getPosition();
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;
    
    sf::Font font;
    font.loadFromFile("arial.tff");
    sf::Text text;
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f,20.f);
    text.setString("HMMMMM");



    //Init Window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Minimap with Background");

    //Init View
    sf::View view;
    view.setSize(1920.f,1080.f);
    view.setCenter(window.getSize().x/2.f, window.getSize().y/2.f);
    float viewSpeed = 200.f;


    //Init game elements
    sf::RectangleShape shape(sf::Vector2f(gridSizeF, gridSizeF));

    while (window.isOpen()) {

        // Update dt
        dt = clock.restart().asSeconds();

        //Update mouse position
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        mousePosGrid.x = mousePosView.x / static_cast<unsigned>(gridSizeF);


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Update
        //Update input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Left
        {
                view.move(viewSpeed*dt,0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Right
        {
                view.move(-viewSpeed*dt,0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Up
        {
                view.move(0.f,viewSpeed*dt);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Down
        {
                view.move(0.f,-viewSpeed*dt);
        }

    //Render
        window.clear();
        window.setView(view);

        window.draw(shape);
        //render game elements

        window.setView(window.getDefaultView());

        //Draw UI
        window.draw(text);

        window.display();
    }

    return 0;
}

