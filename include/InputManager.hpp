#pragma once
#include <SFML/Window.hpp>
#include <functional>
#include <map>

class InputManager {
public:
    // Alias for our action functions (e.g., a void function taking no arguments)
    using Callback = std::function<void()>;

    // Bind a keyboard key to a specific action
    void bindKey(sf::Keyboard::Key key, Callback action) {
        m_keyBindings[key] = action;
    }

    // Call this every frame to check for continuous input
    void update() {
        for (auto const& [key, action] : m_keyBindings) {
            if (sf::Keyboard::isKeyPressed(key)) {
                action();
            }
        }
    }

private:
    std::map<sf::Keyboard::Key, Callback> m_keyBindings;
};
