#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <thread>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Graphing Calculator", sf::Style::Resize | sf::Style::Close);
    sf::RectangleShape incidentRay, refractedRay, boundary, normal;

    boundary.setFillColor(sf::Color::White);
    normal.setFillColor(sf::Color::White);
    incidentRay.setFillColor(sf::Color::Green);
    refractedRay.setFillColor(sf::Color::Red);

    boundary.setSize(sf::Vector2f(400, 0.5));
    normal.setSize(sf::Vector2f(400, 0.5));

    boundary.setPosition(50, 250);
    normal.setPosition(250, 50);
    normal.rotate(90.0f);

    incidentRay.setSize(sf::Vector2f(200, 1));
    refractedRay.setSize(sf::Vector2f(200, 1));

    incidentRay.setOrigin(200, 0.5);
    refractedRay.setOrigin(0, 0.5);

    float refIndex = 1.5f;
    
    for (int incidence = 0; incidence <= 90; incidence += 1) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float refractance = asin(sin(incidence * 3.141592 / 180) / refIndex) * 180 / 3.141592;

        incidentRay.setRotation(90 - incidence);
        refractedRay.setRotation(90 - refractance);
        incidentRay.setPosition(250, 250);
        refractedRay.setPosition(250, 250);

        window.clear(sf::Color::Black);
        window.draw(boundary);
        window.draw(normal);
        window.draw(incidentRay);
        window.draw(refractedRay);
        window.display();

        sf::sleep(sf::milliseconds(100));  // Adding delay for smooth animation
    }

    while (window.isOpen()) {  // Keep the window open after animation ends
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

