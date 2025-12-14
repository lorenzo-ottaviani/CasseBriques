/* ===  INCLUDES  === */

// --- Class Header ---
#include "GameObject.hpp"


/* ===  LIFECYCLE  === */

GameObject::GameObject() 
    : velocity(0.f, 0.f) 
{
}

/* ===  CORE LOGIC  === */

void GameObject::update(float deltaTime) {
    // Basic physics: distance = velocity * time
    // We use the move() method from sf::Transformable
    move(velocity * deltaTime);
}

bool GameObject::checkCollision(const GameObject& other) const {
    // Check if the bounding boxes intersect using SFML's utility
    return getGlobalBounds().intersects(other.getGlobalBounds());
}
