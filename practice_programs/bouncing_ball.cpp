#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Bouncing Ball",sf::Style::Close|sf::Style::Resize);

    sf::CircleShape ball(20.f);
    ball.setFillColor(sf::Color::Blue);
    ball.setPosition(200.f, 200.f);

    sf::Vector2f velocity(3.0f, 2.0f);  // Speed in x and y directions

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move the ball
        ball.move(velocity);

        // Check for collision with window boundaries
        if (ball.getPosition().x <= 0 || ball.getPosition().x + 40 >= 400) {
            velocity.x = -velocity.x;
        }
        if (ball.getPosition().y <= 0 || ball.getPosition().y + 40 >= 400) {
            velocity.y = -velocity.y;
        }

        window.clear();
        window.draw(ball);
        window.display();
    }

    return 0;
}
