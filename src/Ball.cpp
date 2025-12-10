#include "Ball.hpp"

Ball::Ball(float startX, float startY) {
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::White);
    
    // Origin at center (radius, radius) for accurate position handling
    shape.setOrigin(10.f, 10.f); 
    
    setPosition(startX, startY);

    // Initial velocity: moves diagonally up-right
    // -200 Y means "up" in SFML coordinates
    velocity = {250.f, -250.f}; 
}

void Ball::update(float deltaTime) {
    // 1. Move the ball based on its velocity
    GameObject::update(deltaTime); 

    // 2. Screen Collision (Bouncing off walls)
    sf::Vector2f pos = getPosition();

    // Left Wall
    if (pos.x < 10.f) {
        setPosition(10.f, pos.y);   // Correct position to avoid sticking
        velocity.x = -velocity.x;   // Invert horizontal direction
    }
    // Right Wall (800 width - 10 radius)
    else if (pos.x > 790.f) {
        setPosition(790.f, pos.y);
        velocity.x = -velocity.x;
    }

    // Top Wall
    if (pos.y < 10.f) {
        setPosition(pos.x, 10.f);
        velocity.y = -velocity.y;   // Invert vertical direction
    }

    // Bottom Wall (Ground)
    // In a real game, this is "Game Over". For now, we just bounce.
    if (pos.y > 590.f) {
        setPosition(pos.x, 590.f);
        velocity.y = -velocity.y;
    }
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);
}

sf::FloatRect Ball::getGlobalBounds() const {
    return getTransform().transformRect(shape.getGlobalBounds());
}
