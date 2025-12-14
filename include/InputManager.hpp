#pragma once

/* ===  INCLUDES  === */

// --- Standard C++ Libraries ---
#include <functional>
#include <map>

// --- SFML Library ---
#include <SFML/Window.hpp>


/* ===  CLASS DEFINITION  === */

/**
 * @brief Manages keyboard input mapping to specific actions.
 *
 * This class allows binding SFML Keyboard keys to callable functions (lambdas, methods).
 * It polls the state of these keys during the update loop.
 */
class InputManager {
public:
    /* --- Type Definitions --- */

    /**
     * @brief Alias for a void function with no arguments.
     * Used for storing the actions triggered by key presses.
     */
    using Callback = std::function<void()>;

    /* --- Configuration --- */

    /**
     * @brief Binds a specific keyboard key to an action.
     *
     * @param key The SFML Keyboard key to monitor (e.g., sf::Keyboard::Space).
     * @param action The function or lambda to execute when the key is pressed.
     */
    void bindKey(sf::Keyboard::Key key, const Callback& action);

    /* --- Core Logic --- */

    /**
     * @brief Checks the state of all bound keys.
     *
     * If a bound key is currently pressed, its corresponding action is executed immediately.
     * This should be called once per frame in the game loop.
     */
    void update();

private:
    /* --- Members --- */

    // Maps a physical key to a specific action callback
    std::map<sf::Keyboard::Key, Callback> m_keyBindings;
};
