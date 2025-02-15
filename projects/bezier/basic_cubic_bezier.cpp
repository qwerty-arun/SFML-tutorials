#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <vector>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Bezier Curve Implementation",sf::Style::Resize|sf::Style::Close);

    std::vector<sf::Vertex> curve,velocity,acceleration;
	float t; //variable parameter
	/*sf::Vertex P0,P1,P2,P3;*/
	sf::Vector2f P0,P1,P2,P3,P;
	P0.x = 50; P0.y = 100;
	P1.x = 150; P1.y = 400;
	P2.x = 250; P2.y = 100;
	P3.x = 450; P3.y = 350;
	// Implementing the direct forumula: Berstein polynomial for degree 3 curve which uses four points
	for(t = 0.0f; t<=1.0f;t+=0.001f)
	{
		sf::Vector2f vel,acc;
		vel.x = P0.x * (-3*pow(t,2)+6*t-3) + P1.x * (9*pow(t,2)-12*t+3) + P2.x * (-9*pow(t,2)+6*t)+ P3.x*(3*pow(t,2));
		vel.y = P0.y * (-3*pow(t,2)+6*t-3) + P1.y * (9*pow(t,2)-12*t+3) + P2.y * (-9*pow(t,2)+6*t)+ P3.y*(3*pow(t,2));
		acc.x = P0.x * (-6*t+6) + P1.x * (18*t-12) + P2.x * (-18*t+6) + P3.x * (6*t);
		acc.y = P0.y * (-6*t+6) + P1.y * (18*t-12) + P2.y * (-18*t+6) + P3.y * (6*t);
		P.x = P0.x*(-pow(t,3)+3*pow(t,2)-3*t+1) + P1.x*(3*pow(t,3)-6*pow(t,2)+3*t) + P2.x*(-3*pow(t,3)+3*pow(t,2)) + P3.x*(pow(t,3));
		P.y = P0.y*(-pow(t,3)+3*pow(t,2)-3*t+1) + P1.y*(3*pow(t,3)-6*pow(t,2)+3*t) + P2.y*(-3*pow(t,3)+3*pow(t,2)) + P3.y*(pow(t,3));
		curve.push_back(sf::Vertex(sf::Vector2f(P.x,P.y),sf::Color::White));
		velocity.push_back(sf::Vertex(sf::Vector2f(vel.x/10+50,(vel.y)/50+400),sf::Color::Yellow));
		acceleration.push_back(sf::Vertex(sf::Vector2f(acc.x/10+250,(acc.y)/50+400),sf::Color::Green));
	}
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
	window.draw(curve.data(), curve.size(), sf::LinesStrip);
	window.draw(velocity.data(), velocity.size(), sf::LinesStrip);
	window.draw(acceleration.data(), acceleration.size(), sf::LinesStrip);
        window.display();
    }
    return 0;
}
