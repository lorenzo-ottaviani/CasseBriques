/* ===  INCLUDES  === */

// --- Class Header ---
#include "InputManager.hpp"


/* ===  PUBLIC METHODS  === */

void InputManager::bindKey(sf::Keyboard::Key key, const Callback& action) {
    // Store the action in the map associated with the key
    m_keyBindings[key] = action;
}

void InputManager::update() {
    // Iterate through all registered bindings
    for (auto const& [key, action] : m_keyBindings) {
        // If the physical key is currently held down, trigger the action
        if (sf::Keyboard::isKeyPressed(key)) {
            action();
        }
    }
}
