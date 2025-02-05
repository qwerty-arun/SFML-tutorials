#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Smooth Paint App",sf::Style::Resize|sf::Style::Close);

    sf::VertexArray lines(sf::LineStrip); // Stores the line segments
    sf::Color currentColor = sf::Color::Black;  // Default color

    sf::RectangleShape red; red.setSize(sf::Vector2f(40.0f,40.0f)); red.setFillColor(sf::Color::Red); red.setPosition(sf::Vector2f(460.0f,0.0f));
    sf::RectangleShape blue;blue.setSize(sf::Vector2f(40.0f,40.0f));blue.setFillColor(sf::Color::Blue);blue.setPosition(sf::Vector2f(460.0f,40.0f));
    sf::RectangleShape yellow;yellow.setSize(sf::Vector2f(40.0f,40.0f));yellow.setFillColor(sf::Color::Yellow);yellow.setPosition(sf::Vector2f(460.0f,80.0f));
    sf::RectangleShape green;green.setSize(sf::Vector2f(40.0f,40.0f));green.setFillColor(sf::Color::Green);green.setPosition(sf::Vector2f(460.0f,120.0f));
    sf::RectangleShape black;black.setSize(sf::Vector2f(40.0f,40.0f));black.setFillColor(sf::Color::Black);black.setPosition(sf::Vector2f(460.0f,160.0f));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Change color on keypress
            /*if (event.type == sf::Event::KeyPressed) {*/
            /*    if (event.key.code == sf::Keyboard::R) currentColor = sf::Color::Red;*/
            /*    if (event.key.code == sf::Keyboard::G) currentColor = sf::Color::Green;*/
            /*    if (event.key.code == sf::Keyboard::B) currentColor = sf::Color::Blue;*/
            /*    if (event.key.code == sf::Keyboard::Y) currentColor = sf::Color::Yellow;*/
            /*    if (event.key.code == sf::Keyboard::K) currentColor = sf::Color::Black;*/
            /*}*/
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) // use if(event.mouseButton.button == sf::Mouse::Left) if you want only lines
                    {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        /*sf::Vector2f mousePos(event.mouseButton.x,event.mouseButton.y);*/
                        if(red.getGlobalBounds().contains((sf::Vector2f)mousePos)) //not that type casting is happening from into to float so its not a problem as there is not info loss
                        {
                            currentColor=sf::Color::Red;
                        }
                        if(blue.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        {
                            currentColor=sf::Color::Blue;
                        }
                        if(yellow.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        {
                            currentColor=sf::Color::Yellow;
                        }
                        if(green.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        {
                            currentColor=sf::Color::Green;
                        }
                        if(black.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        {
                            currentColor=sf::Color::Black;
                        }
                        lines.append(sf::Vertex(sf::Vector2f(mousePos), currentColor));
                    }
            }

        // Draw only when the left mouse button is held
        /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {*/
        /*    sf::Vector2i mousePos = sf::Mouse::getPosition(window);*/
        /*    lines.append(sf::Vertex(sf::Vector2f(mousePos), currentColor));*/
        /*}*/

        window.clear(sf::Color::White);
        window.draw(lines);  // Draw the smooth line
        window.draw(red);
        window.draw(blue);
        window.draw(yellow);
        window.draw(green);
        window.draw(black);
        window.display();
    }
    return 0;
}
