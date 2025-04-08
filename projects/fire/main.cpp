#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

using namespace sf;
using namespace std;

int main()
{
    // Window setup
    RenderWindow window(VideoMode(800, 600), "Temperature Visualized");
    window.setFramerateLimit(60);

    // Font and label
    Font font;
    font.loadFromFile("arial.ttf");

    Text text("Heat Transfer", font, 24);
    text.setFillColor(Color::White);
    text.setPosition(20.f, 20.f);

    // Particles setup
    CircleShape particle(10.f);
    particle.setFillColor(Color::Red);
    particle.setPosition(100.f, 100.f);
    float temp1 = 400;

    vector<CircleShape> particles;

    // Heat transfer tracking
    struct HeatStage {
        float t1, t2;
        Color color1, color2;
    };

    std::vector<HeatStage> stages = {
        {400, 1000, Color(255, 51, 51), Color(255, 255, 204)},
        {500, 900,  Color(255, 102, 102), Color(255, 255, 153)},
        {600, 800,  Color(255, 128, 0), Color(255, 255, 51)},
        {700, 700,  Color(255, 153, 51), Color(255, 153, 51)},
    };

    Clock clock;
    size_t heatStageIndex = 0;
    bool isTransferring = false;
    Clock transferClock;

    while (window.isOpen()) {
        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            particle.setPosition(Mouse::getPosition().x, Mouse::getPosition().y);
            particles.push_back(CircleShape(particle));
        }

        for(auto& particle1: particles)
        {
            for(auto& particle2: particles)
            {
                // Check collision and start heat transfer
                if (particle1.getGlobalBounds().intersects(particle2.getGlobalBounds()))
                {
                    particle1.setPosition(particle1.getPosition().x - particle2.getRadius() * 2, particle1.getPosition().y);
                    if (!isTransferring) 
                    {
                        isTransferring = true;
                        heatStageIndex = 0;
                        transferClock.restart();
                    }
                    // Heat transfer progress (non-blocking)
                    if (isTransferring && heatStageIndex < stages.size()) 
                    {
                        if (transferClock.getElapsedTime().asMilliseconds() > 1000)
                        {
                            const auto& stage = stages[heatStageIndex];
                            particle1.setFillColor(stage.color1);
                            temp1 = stage.t1;
                            heatStageIndex++;
                            transferClock.restart();
                        }

                    }
                }

            }

        }

        // Draw everything
        window.clear();
        window.draw(text);
        for(auto particle: particles)
            window.draw(particle);
        window.display();
    }
    return 0;
}
