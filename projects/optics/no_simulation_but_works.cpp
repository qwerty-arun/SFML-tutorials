#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <vector>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Graphing Calculator", sf::Style::Resize | sf::Style::Close);
    sf::RectangleShape incidentRay;
    sf::RectangleShape refractedRay;
    sf::RectangleShape boundary;
    sf::RectangleShape normal;

    boundary.setFillColor(sf::Color::White);
    normal.setFillColor(sf::Color::White);

    boundary.setSize(sf::Vector2f(400,0.5));
    normal.setSize(sf::Vector2f(400,0.5));

    boundary.setPosition(50,250);
    normal.setPosition(250,50);
    normal.rotate(90.0f);

    incidentRay.setFillColor(sf::Color::Green);
    refractedRay.setFillColor(sf::Color::Red);
    incidentRay.setSize(sf::Vector2f(200,1));
    refractedRay.setSize(sf::Vector2f(200,1));
    incidentRay.setPosition(250,250);
    refractedRay.setPosition(250,250);
        incidentRay.setOrigin(200,1);

    bool done;
        float refIndex=1.5f;
        /*float incident_angle {45};*/
        /*float refractive_angle = asin(sin(3.141592-incident_angle*3.141592/180)/refIndex);*/
        /*incidentRay.rotate(90-incident_angle);*/
        /*refractedRay.rotate(90-refractive_angle*180/3.141592);*/
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for(int incidence{0};incidence<=90;incidence+=1)
        {
            window.clear(sf::Color::Black);
            float refractance=asin(sin(3.141592-incidence*3.141592/180)/refIndex);
            incidentRay.rotate(90-incidence);
            refractedRay.rotate(90-refractance*180/3.141592);
            window.draw(incidentRay);
            window.draw(refractedRay);
        }
        window.draw(boundary);
        window.draw(normal);

        window.display();
    }

    return 0;
}
