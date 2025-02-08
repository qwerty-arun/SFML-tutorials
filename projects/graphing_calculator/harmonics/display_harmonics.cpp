#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Graphing Calculator", sf::Style::Resize | sf::Style::Close);
    
    std::vector<sf::Vertex> graph1Stroke;
    std::vector<sf::Vertex> squareWave;
    sf::Vector2f offset_1(50.0f,180.0f);

    for(int k=1;k<=4;k++)
    {
        for (float x = 0.0f; x <= 19.f; x += 0.01f) {
            graph1Stroke.push_back(sf::Vertex(sf::Vector2f(20 * x + offset_1.x, -40 * sin((2*k-1) * x)/(2*k-1) + offset_1.y), sf::Color::Yellow));
        }
        for(int i=0;i<graph1Stroke.size();i++)
        {
            float x = graph1Stroke[i].position.x;
            float y = graph1Stroke[i].position.y;
            squareWave.push_back(sf::Vertex(sf::Vector2f(x,y+offset_1.y),sf::Color::Green));
        }
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(&graph1Stroke[0], graph1Stroke.size(), sf::LineStrip);
        window.display();
    }

    return 0;
}
