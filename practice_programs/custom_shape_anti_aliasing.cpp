#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <iostream>
using namespace sf;
class EllipseShape : public sf::Shape
{
public:
    explicit EllipseShape(sf::Vector2f radius = {0, 0}) : m_radius(radius)
    {
        update();
    }

    void setRadius(sf::Vector2f radius)
    {
        m_radius = radius;
        update();
    }

    sf::Vector2f getRadius() const
    {
        return m_radius;
    }

    std::size_t getPointCount() const override
    {
        return 30; // fixed, but could be an attribute of the class if needed
    }

    sf::Vector2f getPoint(std::size_t index) const override
    {
        static constexpr float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x     = std::cos(angle) * m_radius.x;
        float y     = std::sin(angle) * m_radius.y;

        return m_radius + sf::Vector2f(x, y);
    }

private:
    sf::Vector2f m_radius;
};


// Function to create a thick line using Quads
int main() {
    /*sf::RenderWindow window(sf::VideoMode(600, 400), "Thick Line",sf::Style::Resize|sf::Style::Close);*/
    // Create a thick line
    std::vector line={
    sf::Vertex{sf::Vector2f(10.f, 10.f)},
    sf::Vertex{sf::Vector2f(150.f, 150.f)}
};
sf::ContextSettings settings;
settings.antialiasingLevel = 8;

sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML shapes", sf::Style::Default,settings);
    EllipseShape ellipse;
    ellipse.setRadius(sf::Vector2f(100.f,100.f));
    ellipse.setFillColor(sf::Color::Red);
    ellipse.setPosition(100.f,100.f);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Vector2f point=ellipse.getPoint(2);
        std::cout << point.x<< " "<<point.y<<'\n';
        window.clear();
        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
        window.draw(ellipse);
        window.display();
    }
    return 0;
}
