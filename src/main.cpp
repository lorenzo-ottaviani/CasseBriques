#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "InputManager.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"

// Define the possible states of the game
enum class GameState {
    Running,
    GameOver,
    Victory
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout - Step 4: Win & Lose");
    window.setFramerateLimit(60);

    // --- 0. Resources (Font & Text) ---
    sf::Font font;
    // Load the font. Make sure "arial.ttf" is in the cmake-build-debug folder!
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "ERROR: Could not load arial.ttf. Check your build directory." << std::endl;
        // The game will continue, but text won't show up.
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    // Helper lambda to center text on the screen
    auto centerText = [&](const std::string& str) {
        text.setString(str);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
        text.setPosition(400.f, 300.f); // Center of the window
    };

    // --- 1. Create Game Objects ---
    Paddle paddle(400, 550);
    Ball ball(400, 300);
    std::vector<Brick> bricks;

    // --- Grid Generation ---
    constexpr int rows = 5;
    for (int i = 0; i < rows; ++i) {
        constexpr int cols = 10;
        for (int j = 0; j < cols; ++j) {
            constexpr float startX = 130.f;
            constexpr float startY = 60.f;
            float x = startX + static_cast<float>(j) * 65.f;
            float y = startY + static_cast<float>(i) * 25.f;
            bricks.emplace_back(x, y);
        }
    }

    // --- 2. Setup Inputs ---
    InputManager inputs;
    inputs.bindKey(sf::Keyboard::Left,  [&paddle](){ paddle.move(-paddle.speed * 0.016f, 0.f); });
    inputs.bindKey(sf::Keyboard::Right, [&paddle](){ paddle.move(paddle.speed * 0.016f, 0.f); });

    // Optional: Space to restart (logic not implemented yet, but ready)
    inputs.bindKey(sf::Keyboard::Space, [](){ /* Restart logic could go here */ });

    sf::Clock clock;
    GameState gameState = GameState::Running;

    // --- 3. Game Loop ---
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        inputs.update(); // Keep inputs active (for quitting or restarting later)

        // --- UPDATE LOGIC (Only runs if the game is active) ---
        if (gameState == GameState::Running) {
            paddle.update(deltaTime);
            ball.update(deltaTime);

            // A. Collision: Ball vs Paddle
            if (paddle.checkCollision(ball)) {
                ball.velocity.y = -std::abs(ball.velocity.y); // Force bounce UP
                ball.move(0.f, -10.f); // Nudge up to prevent sticking
            }

            // B. Collision: Ball vs Bricks
            for (auto& brick : bricks) {
                // Check collision only if the brick is still active (not destroyed)
                if (!brick.isDestroyed && brick.checkCollision(ball)) {
                    brick.isDestroyed = true;           // Mark as broken
                    ball.velocity.y = -ball.velocity.y; // Simple vertical bounce
                    break; // Stop checking to prevent hitting two bricks in one frame
                }
            }

            // C. Check Victory (Count active bricks AFTER collision checks)
            int remainingBricks = 0;
            for (const auto& brick : bricks) {
                if (!brick.isDestroyed) {
                    remainingBricks++;
                }
            }

            // If no bricks are left, switch state to Victory
            if (remainingBricks == 0) {
                gameState = GameState::Victory;
                centerText("VICTORY!");
            }

            // D. Check Defeat (Game Over)
            // If the ball falls below the screen height (600px)
            if (ball.getPosition().y > 600.f) {
                gameState = GameState::GameOver;
                centerText("GAME OVER");
                text.setFillColor(sf::Color::Red);
            }
        }

        // --- RENDER ---
        window.clear(sf::Color::Black);

        if (gameState == GameState::Running) {
            // Draw Game
            for (const auto& brick : bricks) {
                brick.draw(window, sf::RenderStates::Default);
            }
            window.draw(paddle);
            window.draw(ball);
        }
        else {
            // Draw End Screen (Text only)
            // You could draw the game in the background if you want,
            // but we keep it black for simplicity.
            window.draw(text);
        }

        window.display();
    }

    return 0;
}
