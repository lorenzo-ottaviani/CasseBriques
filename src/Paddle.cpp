/* ===  INCLUDES  === */

// --- Class Header ---
#include "Paddle.hpp"


/* ===  LIFECYCLE  === */

Paddle::Paddle(float startX, float startY) {
    // 1. Visual Setup
    shape.setSize({100.f, 20.f}); // Width: 100, Height: 20
    shape.setFillColor(sf::Color::Cyan);

    // Set origin to the center of the rectangle (Half Width, Half Height).
    // This means setPosition(x,y) places the CENTER of the paddle at x,y.
    shape.setOrigin(50.f, 10.f);

    // 2. Position & Physics
    setPosition(startX, startY);
    speed = 600.f; // Fast enough for reactive gameplay
}


/* ===  CORE LOGIC  === */

void Paddle::update(float deltaTime) {
    // Note: Movement is driven by InputManager (Game.cpp) calling move().
    // Here, we only handle constraints (keeping the paddle inside the window).

    sf::Vector2f pos = getPosition();
    constexpr float halfWidth = 50.f;
    constexpr float windowWidth = 800.f;

    // Left limit (x < half_width)
    if (pos.x < halfWidth) {
        setPosition(halfWidth, pos.y);
    }
    // Right limit (x > window_width - half_width)
    else if (pos.x > windowWidth - halfWidth) {
        setPosition(windowWidth - halfWidth, pos.y);
    }
}


/* ===  GRAPHICS  === */

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Apply the GameObject's transform (position) to the shape
    states.transform *= getTransform();
    target.draw(shape, states);
}

sf::FloatRect Paddle::getGlobalBounds() const {
    // Transform local bounds to world bounds
    return getTransform().transformRect(shape.getGlobalBounds());
}
