// this is messed up, gotta try memory efficient method
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Projected Cube");

    std::vector<sf::Vertex> outerEdges;
    outerEdges.push_back(sf::Vertex(sf::Vector2f(100,100),sf::Color::White));
    outerEdges.push_back(sf::Vertex(sf::Vector2f(250,100),sf::Color::White));
    outerEdges.push_back(sf::Vertex(sf::Vector2f(250,250),sf::Color::White));
    outerEdges.push_back(sf::Vertex(sf::Vector2f(100,250),sf::Color::White));
    outerEdges.push_back(sf::Vertex(sf::Vector2f(100,100),sf::Color::White));

    std::vector<sf::Vertex> innerEdges;
    innerEdges.push_back(sf::Vertex(sf::Vector2f(125,125),sf::Color::White));
    innerEdges.push_back(sf::Vertex(sf::Vector2f(225,125),sf::Color::White));
    innerEdges.push_back(sf::Vertex(sf::Vector2f(225,225),sf::Color::White));
    innerEdges.push_back(sf::Vertex(sf::Vector2f(125,225),sf::Color::White));
    innerEdges.push_back(sf::Vertex(sf::Vector2f(125,125),sf::Color::White));

    std::vector<sf::Vertex> slants[4];
    slants[0].push_back(sf::Vertex(sf::Vector2f(100,100),sf::Color::White));
    slants[0].push_back(sf::Vertex(sf::Vector2f(125,125),sf::Color::White));

    slants[1].push_back(sf::Vertex(sf::Vector2f(250,100),sf::Color::White));
    slants[1].push_back(sf::Vertex(sf::Vector2f(225,125),sf::Color::White));

    slants[2].push_back(sf::Vertex(sf::Vector2f(250,250),sf::Color::White));
    slants[2].push_back(sf::Vertex(sf::Vector2f(225,225),sf::Color::White));

    slants[3].push_back(sf::Vertex(sf::Vector2f(100,250),sf::Color::White));
    slants[3].push_back(sf::Vertex(sf::Vector2f(125,225),sf::Color::White));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        if (!outerEdges.empty())
            window.draw(outerEdges.data(), outerEdges.size(), sf::LinesStrip);
        if (!innerEdges.empty())
            window.draw(innerEdges.data(), innerEdges.size(), sf::LinesStrip);
        if (!slants[0].empty())
            window.draw(slants[0].data(), slants[0].size(), sf::LinesStrip);
        if (!slants[1].empty())
            window.draw(slants[1].data(), slants[1].size(), sf::LinesStrip);
        if (!slants[2].empty())
            window.draw(slants[2].data(), slants[2].size(), sf::LinesStrip);
        if (!slants[3].empty())
            window.draw(slants[3].data(), slants[3].size(), sf::LinesStrip);
        window.display();
    }

    return 0;
}
