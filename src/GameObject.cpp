#include "GameObject.hpp"

GameObject::GameObject() : velocity(0.f, 0.f) {}

void GameObject::update(float deltaTime) {
    // Basic physics: distance = velocity * time
    move(velocity * deltaTime);
}

bool GameObject::checkCollision(const GameObject& other) const {
    // Check if the bounding boxes intersect
    return getGlobalBounds().intersects(other.getGlobalBounds());
}
