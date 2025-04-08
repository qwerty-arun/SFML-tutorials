#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minimap with Background");

    // Big world
    sf::RectangleShape world(sf::Vector2f(2000, 2000));
    world.setFillColor(sf::Color(70, 70, 70));  // darker background

    // Player
    sf::CircleShape player(25);
    player.setFillColor(sf::Color::Cyan);
    player.setPosition(1000, 1000);

    // Main view
    sf::View mainView(sf::FloatRect(0, 0, 800, 600));
    mainView.setCenter(player.getPosition());

    // Minimap view
    sf::View minimapView(sf::FloatRect(0, 0, 2000, 2000));
    minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.24f, 0.24f)); // Top-right

    // Background for minimap (slightly smaller so it doesn't overwrite the edges)
    sf::RectangleShape minimapBG;
    minimapBG.setSize(sf::Vector2f(800 * 0.24f, 600 * 0.24f));
    minimapBG.setFillColor(sf::Color(100, 0, 0)); // semi-transparent black
    minimapBG.setPosition(800 * 0.75f, 600 * 0.0f);  // match viewport

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move(0, 5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move(5, 0);

        mainView.setCenter(player.getPosition());

        // ----------- DRAWING -------------
        window.clear();

        // Draw main game world
        window.setView(mainView);
        window.draw(world);
        window.draw(player);

        // Reset to default view to draw the background of the minimap
        window.setView(window.getDefaultView());
        window.draw(minimapBG);

        // Draw actual minimap content
        window.setView(minimapView);
        window.draw(world);
        window.draw(player);

        window.display();
    }

    return 0;
}

