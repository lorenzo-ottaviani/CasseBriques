#include <SFML/Graphics.hpp>
#include <cmath>
#include "InputManager.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout - Step 2: Physics");
    window.setFramerateLimit(60);

    // 1. Create Game Objects
    Paddle paddle(400, 550); // Center bottom
    Ball ball(400, 300);     // Center screen

    // 2. Setup Inputs
    InputManager inputs;

    // We move the paddle manually. The Paddle::update() will ensure it stays on screen.
    inputs.bindKey(sf::Keyboard::Left,  [&paddle](){ paddle.move(-paddle.speed * 0.016f, 0.f); });
    inputs.bindKey(sf::Keyboard::Right, [&paddle](){ paddle.move(paddle.speed * 0.016f, 0.f); });

    sf::Clock clock;

    // 3. Game Loop
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- Update ---
        inputs.update();          // Handle keyboard
        paddle.update(deltaTime); // Constrain paddle
        ball.update(deltaTime);   // Move ball & bounce walls

        // --- Collision Logic (Ball vs Paddle) ---
        if (paddle.checkCollision(ball)) {
            // Simple bounce: reverse Y velocity to go up
            // std::abs ensures it always goes UP, even if hit from weird angle
            ball.velocity.y = -std::abs(ball.velocity.y);

            // Nudge ball up slightly to prevent sticking inside the paddle
            ball.move(0.f, -10.f);
        }

        // --- Render ---
        window.clear(sf::Color::Black);
        window.draw(paddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}
