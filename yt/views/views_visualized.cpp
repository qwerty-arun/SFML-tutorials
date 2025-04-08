#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "View with Outline");
    
    // Create a smaller view
    sf::View view(sf::FloatRect(0, 0, 400, 300));
    view.setCenter(400, 300); 

    // Simulated outline (Rectangle)
    sf::RectangleShape viewOutline(sf::Vector2f(400, 300)); // Same size as view
    viewOutline.setFillColor(sf::Color::Transparent);
    viewOutline.setOutlineColor(sf::Color::Green);
    viewOutline.setOutlineThickness(5.f);
    
    sf::RectangleShape box(sf::Vector2f(100, 100)); // An object in world
    box.setFillColor(sf::Color::Red);
    box.setPosition(400, 300);
    box.setOrigin(50, 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.zoom(0.99f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.zoom(1.01f);
        // Rotate the VIEW (camera)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            view.rotate(-1.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            view.rotate(1.f);

        // Rotate the BOX (independent of view)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            box.rotate(-1.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            box.rotate(1.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            view.move(0.f,5.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            view.move(0.f,-5.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            view.move(5.f,0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            view.move(-5.f,0.f);
        }


        // Update outline position to match view
        viewOutline.setPosition(view.getCenter().x - 200, view.getCenter().y - 150);
        viewOutline.setRotation(view.getRotation()); // Rotate with view

        window.setView(view); // Apply camera view
        window.clear();
        window.draw(box);
        
        // Reset to default view and draw outline
        window.setView(window.getDefaultView());
        window.draw(viewOutline);

        window.display();
    }
    return 0;
}

