#include "Paddle.hpp"

Paddle::Paddle(float startX, float startY) {
    shape.setSize({100.f, 20.f}); // Width: 100, Height: 20
    shape.setFillColor(sf::Color::Cyan);

    // Set origin to the center. This means setPosition(x,y) places the CENTER of the paddle at x,y.
    // Useful for calculations later.
    shape.setOrigin(50.f, 10.f);

    setPosition(startX, startY);
    speed = 600.f; // Fast enough for smooth gameplay
}

void Paddle::update(float deltaTime) {
    // 1. We don't move the paddle here automatically (movement is driven by InputManager in main).
    //    However, if we used velocity-based movement, we would call move(velocity * deltaTime).

    // 2. Boundary Checks: Constrain the paddle within the screen (Window width = 800)
    sf::Vector2f pos = getPosition();

    // Left limit (x < half_width)
    if (pos.x < 50.f) {
        setPosition(50.f, pos.y);
    }
    // Right limit (x > window_width - half_width)
    else if (pos.x > 750.f) {
        setPosition(750.f, pos.y);
    }
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Apply the GameObject's transform (position/rotation) to the shape before drawing
    states.transform *= getTransform();
    target.draw(shape, states);
}

sf::FloatRect Paddle::getGlobalBounds() const {
    // Return the bounding box transformed by the current position
    return getTransform().transformRect(shape.getGlobalBounds());
}
