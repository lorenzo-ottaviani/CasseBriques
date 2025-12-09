#include <SFML/Graphics.hpp>
#include "InputManager.hpp"
#include "GameObject.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout - Step 1");
    window.setFramerateLimit(60);

    // 1. Create Test Objects
    // Player object (Cyan square)
    SimpleShape player(sf::Vector2f(50.f, 50.f), sf::Color::Cyan);
    player.setPosition(400, 300);

    // Obstacle object (White square)
    SimpleShape obstacle(sf::Vector2f(80.f, 80.f), sf::Color::White);
    obstacle.setPosition(200, 200);

    // 2. Setup Input Manager
    InputManager inputs;
    float speed = 300.f;

    // Bind keys to lambda functions
    // Note: We capture 'player' by reference (&) to modify it
    inputs.bindKey(sf::Keyboard::Left,  [&player, speed](){ player.move(-speed * 0.016f, 0.f); });
    inputs.bindKey(sf::Keyboard::Right, [&player, speed](){ player.move(speed * 0.016f, 0.f); });
    inputs.bindKey(sf::Keyboard::Up,    [&player, speed](){ player.move(0.f, -speed * 0.016f); });
    inputs.bindKey(sf::Keyboard::Down,  [&player, speed](){ player.move(0.f, speed * 0.016f); });
    inputs.bindKey(sf::Keyboard::R,     [&player](){ player.rotate(2.f); });

    sf::Clock clock;

    // 3. Main Game Loop
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        // float deltaTime = dt.asSeconds(); // Not used in main scope yet

        // --- Event Polling ---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- Update ---
        inputs.update(); // Handle continuous input

        // Simple Collision Test
        if (player.checkCollision(obstacle)) {
            obstacle.shape.setFillColor(sf::Color::Red); // Visual feedback
        } else {
            obstacle.shape.setFillColor(sf::Color::White);
        }

        // --- Render ---
        window.clear();
        window.draw(obstacle);
        window.draw(player);
        window.display();
    }

    return 0;
}
