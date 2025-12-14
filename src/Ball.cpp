/* ===  INCLUDES  === */

// --- Class Header ---
#include "Ball.hpp"


/* ===  LIFECYCLE  === */

Ball::Ball(float startX, float startY) {
    // 1. Visual Setup
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::White);
    
    // Origin at center (radius, radius) makes physics and rotation easier
    shape.setOrigin(10.f, 10.f); 
    
    // 2. Position Setup
    setPosition(startX, startY);

    // 3. Physics Setup
    // Initial velocity: moves diagonally up-right
    // Y is negative because 0 is at the top of the screen
    velocity = {250.f, -250.f}; 
}


/* ===  CORE LOGIC  === */

void Ball::update(float deltaTime) {
    // 1. Move the ball (Parent logic: pos += velocity * dt)
    GameObject::update(deltaTime); 

    // 2. Screen Collision (Bouncing off walls)
    sf::Vector2f pos = getPosition();
    constexpr float radius = 10.f;

    // Left Wall
    if (pos.x < radius) {
        setPosition(radius, pos.y); // Correct position to avoid sticking
        velocity.x = -velocity.x;   // Bounce horizontally
    }
    // Right Wall (Window Width 800 - Radius 10)
    else if (pos.x > 800.f - radius) {
        setPosition(800.f - radius, pos.y);
        velocity.x = -velocity.x;
    }

    // Top Wall
    if (pos.y < radius) {
        setPosition(pos.x, radius);
        velocity.y = -velocity.y;   // Bounce vertically
    }
    
    // Note: Bottom wall is not handled here because it triggers Game Over in Game.cpp
}


/* ===  GRAPHICS  === */

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Apply the GameObject's transform (position/rotation) to the shape
    states.transform *= getTransform();
    target.draw(shape, states);
}

sf::FloatRect Ball::getGlobalBounds() const {
    // Transform the local shape bounds into global world coordinates
    return getTransform().transformRect(shape.getGlobalBounds());
}