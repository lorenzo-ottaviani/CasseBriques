#pragma once
#include <SFML/Window.hpp>
#include <functional>
#include <map>

class InputManager {
public:
    using Callback = std::function<void()>;

    // CHANGE: Added 'const' and '&' to pass by reference instead of value
    void bindKey(sf::Keyboard::Key key, const Callback& action);

    void update();

private:
    std::map<sf::Keyboard::Key, Callback> m_keyBindings;
};
