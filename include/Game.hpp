#pragma once

/* ===  INCLUDES  === */

// --- Standard C++ Libraries ---
#include <string>
#include <vector>

// --- SFML Library ---
#include <SFML/Graphics.hpp>

// --- Project Systems ---
#include "InputManager.hpp"

// --- Game Entities ---
#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"


/* ===   TYPE DEFINITIONS   === */

/**
 * @brief Represents the possible states of the game execution.
 */
enum class GameState {
    Running,    ///< The game is currently being played.
    GameOver,   ///< The player has lost (ball fell).
    Victory     ///< The player has destroyed all bricks.
};

/* ===   CLASS DEFINITION  === */

/**
 * @brief The main Game engine.
 *
 * This class manages the window, the game loop, user inputs,
 * and coordinates all game objects (Paddle, Ball, Bricks).
 */
class Game {
public:
    /* --- Lifecycle --- */

    /**
     * @brief Construct a new Game object.
     *
     * Initializes the window, loads resources (fonts), and sets up the first level.
     */
    Game();

    /**
     * @brief Destroy the Game object.
     * Default destructor.
     */
    ~Game() = default;

    /* --- Execution --- */

    /**
     * @brief Starts the main game loop.
     *
     * This method contains the while(window.isOpen()) loop.
     * It handles events, updates logic, and renders the frame.
     */
    void run();

private:
    /* --- Core Methods --- */

    /**
     * @brief Polls and processes window events.
     * Handles window closing and basic input events.
     */
    void processEvents();

    /**
     * @brief Updates the game logic for the current frame.
     *
     * Handles movement, physics, and collision detection for all entities.
     *
     * @param deltaTime The time elapsed since the last frame (in seconds).
     */
    void update(float deltaTime);

    /**
     * @brief Renders all game objects to the window.
     *
     * Clears the screen, draws entities based on the current GameState, and displays the buffer.
     */
    void render();

    /* --- Helper Methods --- */

    /**
     * @brief Resets the game level to its initial state.
     *
     * Repositions the paddle and ball, and regenerates the grid of bricks.
     * Used at startup and when restarting the game.
     */
    void resetLevel();

    /**
     * @brief Configures and centers the text message on the screen.
     *
     * Used for "GAME OVER" or "VICTORY" messages.
     *
     * @param str The string message to display.
     */
    void centerText(const std::string& str);

    /* --- Members --- */
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
