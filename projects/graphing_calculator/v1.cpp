// First two waves are being displayed correclty, but the third one isn't
// Reason: graph1Stroke and graph2Stroke are being cleared after each loop iteration after appending to graph1 and graph2, therefore graph3Stroke doen't have valid values from graph1Stroke[i] and graph2Stroke[i]
// pushing graph1Stroke and graph2Stroke into graph1 and graph2 inside the loop, it should be done after creating the entire stroke
// Incorrect access to graph1Storke[i].position. graph1Stroke and graph2Stroke are getting reset, so they don't hold values for i
// I was also adding x coordinates in the third graph whereas it should be the same and only y coordinates should be added
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Graphing Calci", sf::Style::Resize | sf::Style::Close);
    std::vector<sf::VertexArray> graph1; // Stores all the drawn strokes
    std::vector<sf::VertexArray> graph2; // Stores all the drawn strokes
    std::vector<sf::VertexArray> graph3; // Stores all the drawn strokes
    sf::VertexArray graph1Stroke(sf::LineStrip); // Stores the current stroke
    sf::VertexArray graph2Stroke(sf::LineStrip); // Stores the current stroke
    sf::VertexArray graph3Stroke(sf::LineStrip); // Stores the current stroke

    sf::Vector2f offset_1(50.0f,30.f);
    sf::Vector2f offset_2(50.0f,230.f);
    sf::Vector2f offset_3(50.0f,330.f);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            }

        for(float i{0.0f};i<=19.f;i+=0.01)
        {
            graph1Stroke.append(sf::Vertex(sf::Vector2f(20*i+offset_1.x,-20*sin(1*i)+offset_1.y),sf::Color::Yellow));
            graph1.push_back(graph1Stroke);
            graph2Stroke.append(sf::Vertex(sf::Vector2f(20*i+offset_2.x,-20*sin(2*i)+offset_2.y),sf::Color::Red));
            graph2.push_back(graph2Stroke);
}
        for(float i{0.0f};i<=19.f;i+=0.01)
        {
            graph3Stroke.append(sf::Vertex(sf::Vector2f(10*graph1Stroke[i].position.x+10*graph2Stroke[i].position.x+offset_3.x,10*graph1Stroke[i].position.y+10*graph2Stroke[i].position.y+offset_3.y),sf::Color::Green));
            graph3.push_back(graph3Stroke);
        }
            graph1Stroke = sf::VertexArray(sf::LineStrip); //if commented out, then then a line will be drawn between starting and ending points
            graph2Stroke = sf::VertexArray(sf::LineStrip); //if commented out, then then a line will be drawn between starting and ending points
            graph3Stroke = sf::VertexArray(sf::LineStrip); //if commented out, then then a line will be drawn between starting and ending points
        window.clear(sf::Color::Black);
        for (const auto& stroke : graph1) {
            window.draw(stroke);
        }

        for (const auto& stroke : graph2) {
            window.draw(stroke);
        }

        for (const auto& stroke : graph3) {
            window.draw(stroke);
        }
        window.display();
    }
    return 0;
}
