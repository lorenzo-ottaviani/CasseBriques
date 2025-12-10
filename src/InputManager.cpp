#include "InputManager.hpp"

void InputManager::bindKey(sf::Keyboard::Key key, const Callback& action) {
    m_keyBindings[key] = action;
}

void InputManager::update() {
    for (auto const& [key, action] : m_keyBindings) {
        if (sf::Keyboard::isKeyPressed(key)) {
            action();
        }
    }
}
