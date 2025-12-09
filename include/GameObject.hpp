#pragma once
#include <SFML/Graphics.hpp>

// Base class representing any object in the game
class GameObject : public sf::Drawable, public sf::Transformable {
public:
    sf::Vector2f velocity; // Movement speed (x, y)

    GameObject();
    virtual ~GameObject() = default;

    // Update logic (physics, movement, etc.)
    virtual void update(float deltaTime);

    // Pure virtual method: every child MUST define its bounding box for collisions
    virtual sf::FloatRect getGlobalBounds() const = 0;

    // AABB (Axis-Aligned Bounding Box) collision check
    bool checkCollision(const GameObject& other) const;
};

// --- Temporary Test Class for Step 1 ---
class SimpleShape : public GameObject {
public:
    sf::RectangleShape shape;

    SimpleShape(sf::Vector2f size, sf::Color color) {
        shape.setSize(size);
        shape.setFillColor(color);
        shape.setOrigin(size / 2.f); // Set origin to center for rotation
    }

    // We must implement draw from sf::Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        // Apply the parent's transformation (position/rotation) to the shape
        states.transform *= getTransform();
        target.draw(shape, states);
    }

    // We must implement getGlobalBounds from GameObject
    sf::FloatRect getGlobalBounds() const override {
        return getTransform().transformRect(shape.getGlobalBounds());
    }
};
