#pragma once
#include <SFML/Graphics.hpp>

// Base class representing any object in the game
class GameObject : public sf::Drawable, public sf::Transformable {
public:
    sf::Vector2f velocity; // Movement speed (x, y)

    GameObject();
    ~GameObject() override = default;

    // Update logic (physics, movement, etc.)
    virtual void update(float deltaTime);

    // Pure virtual method: every child MUST define its bounding box for collisions
    virtual sf::FloatRect getGlobalBounds() const = 0;

    // AABB (Axis-Aligned Bounding Box) collision check
    bool checkCollision(const GameObject& other) const;
};
