/* ===  INCLUDES  === */

// --- Class Header ---
#include "Brick.hpp"


/* ===  LIFECYCLE  === */

Brick::Brick(float x, float y) {
    // 1. Visual Setup
    shape.setSize({60.f, 20.f}); // Width 60, Height 20
    shape.setFillColor(sf::Color::Yellow);
    
    // Set origin to center (30, 10) for easier positioning logic
    shape.setOrigin(30.f, 10.f); 
    
    // 2. Position Setup
    setPosition(x, y);
}


/* ===  CORE LOGIC  === */

void Brick::update(float deltaTime) {
    // Bricks are static, nothing to update for movement.
    // Future improvement: Add a "wobble" or "fade out" effect here when hit.
    (void)deltaTime; // Prevent "unused parameter" warning
}


/* ===  GRAPHICS  === */

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Only draw if the brick is still "alive"
    if (!isDestroyed) {
        states.transform *= getTransform();
        target.draw(shape, states);
    }
}

sf::FloatRect Brick::getGlobalBounds() const {
    // Transform local bounds to world bounds
    return getTransform().transformRect(shape.getGlobalBounds());
}
