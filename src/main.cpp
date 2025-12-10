#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "InputManager.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout - Step 3: Bricks");
    window.setFramerateLimit(60);

    // --- 1. Create Game Objects ---
    Paddle paddle(400, 550);
    Ball ball(400, 300);

    // Create a grid of bricks
    std::vector<Brick> bricks;

    // --- Grid Generation ---
    // Grid settings: 5 rows
    constexpr int rows = 5;

    for (int i = 0; i < rows; ++i) {
        constexpr int cols = 10;

        for (int j = 0; j < cols; ++j) {
            constexpr float startX = 130.f;
            constexpr float startY = 60.f;

            // Calculate position: Start + (Index * (Size + Spacing))
            // Static_cast avoids "narrowing conversion" warnings
            float x = startX + static_cast<float>(j) * 65.f;
            float y = startY + static_cast<float>(i) * 25.f;

            bricks.emplace_back(x, y);
        }
    }

    // --- 2. Setup Inputs ---
    InputManager inputs;
    inputs.bindKey(sf::Keyboard::Left,  [&paddle](){ paddle.move(-paddle.speed * 0.016f, 0.f); });
    inputs.bindKey(sf::Keyboard::Right, [&paddle](){ paddle.move(paddle.speed * 0.016f, 0.f); });

    sf::Clock clock;

    // --- 3. Game Loop ---
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- Update ---
        inputs.update();
        paddle.update(deltaTime);
        ball.update(deltaTime);

        // --- Collision: Ball vs Paddle ---
        if (paddle.checkCollision(ball)) {
            ball.velocity.y = -std::abs(ball.velocity.y); // Force UP
            ball.move(0.f, -10.f);
        }

        // --- Collision: Ball vs Bricks ---
        // We use a reference (&) to modify the brick directly in the vector
        for (auto& brick : bricks) {
            // Only check collision if the brick is NOT destroyed
            if (!brick.isDestroyed && brick.checkCollision(ball)) {

                // 1. Destroy the brick
                brick.isDestroyed = true;

                // 2. Bounce the ball
                // Simple physics: just invert Y (vertical bounce)
                // (Perfect block physics is complex, this is "good enough" for Step 3)
                ball.velocity.y = -ball.velocity.y;

                // Optimization: Break here? No, ball could hit 2 bricks at once theoretically.
                // But generally, we only want one bounce per frame.
                break;
            }
        }

        // --- Render ---
        window.clear(sf::Color::Black);

        // Draw bricks
        for (const auto& brick : bricks) {
            brick.draw(window, sf::RenderStates::Default);
        }

        window.draw(paddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}
