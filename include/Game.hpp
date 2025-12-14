#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "InputManager.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"

// Represents the possible states of the game
enum class GameState {
    Running,
    GameOver,
    Victory
};

class Game {
public:
    Game();
    ~Game() = default;

    // Main entry point: runs the game loop
    void run();

private:
    // --- Core Methods ---
    void processEvents();
    void update(float deltaTime);
    void render();

    // --- Helper Methods ---
    void resetLevel(); // Generates bricks and resets positions
    void centerText(const std::string& str);

    // --- Members ---
    sf::RenderWindow m_window;
    InputManager m_inputManager;
    GameState m_state;

    // Game Objects
    Paddle m_paddle;
    Ball m_ball;
    std::vector<Brick> m_bricks;

    // Resources
    sf::Font m_font;
    sf::Text m_text;
};
