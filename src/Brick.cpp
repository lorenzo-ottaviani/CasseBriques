#include "Brick.hpp"

Brick::Brick(float x, float y) {
    shape.setSize({60.f, 20.f}); // Width 60, Height 20
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(30.f, 10.f); // Origin at center
    setPosition(x, y);
}

void Brick::update(float deltaTime) {
    // Bricks are static, nothing to update for movement.
    // However, we could add animations here later.
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!isDestroyed) {
        states.transform *= getTransform();
        target.draw(shape, states);
    }
}

sf::FloatRect Brick::getGlobalBounds() const {
    return getTransform().transformRect(shape.getGlobalBounds());
}
