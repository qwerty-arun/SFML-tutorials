#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/Mouse.hpp>
#include <execution>
#include <vector>

using namespace sf;
using namespace std;

class sandParticle
{
    public: 
        CircleShape circle;
        Vector2f position;
        Vector2f velocity;
        Vector2f direction;
        float acceleration = 1.f;
        Clock clock;
        
        void setRadius(float R = 10.f)
        {
            circle.setRadius(R);
        }
        void setColor(Color color)
        {
            circle.setFillColor(color);
        }

        void update()
        {
            float dt = clock.restart().asSeconds();
            if(velocity.y < 25)
            {
                velocity.y += acceleration*direction.y * dt * 30;
            }
        }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Gravity");

    vector<sandParticle> particles;
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Condition 
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            sandParticle newParticle;
            newParticle.position.x = Mouse::getPosition().x;
            newParticle.position.y = Mouse::getPosition().y;

            newParticle.velocity.x = 0.f;
            newParticle.velocity.y = 0.f;

            newParticle.direction.x = 0;
            newParticle.direction.y = 1;

            newParticle.setRadius();
            newParticle.setColor(Color::White);
            particles.push_back(sandParticle(newParticle));
        }
        window.clear(Color::Black);
        //Update the particle
            
        for(int i =0;i<particles.size();i++)
        {
            particles[i].update();
            window.draw(particles[i].circle);
        }
        window.display();
    }
    return 0;
}
