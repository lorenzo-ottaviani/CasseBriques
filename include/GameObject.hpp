#pragma once

/* ===  INCLUDES  === */

// --- SFML Library ---
#include <SFML/Graphics.hpp>


/* ===   CLASS DEFINITION   === */

/**
 * @brief Base class representing any visible and movable object in the game.
 *
 * Inherits from:
 * - sf::Drawable: Allows the object to be drawn (requires implementing draw()).
 * - sf::Transformable: Gives the object position, rotation, and scale.
 */
class GameObject : public sf::Drawable, public sf::Transformable {
public:
    /* --- Public Members --- */

    /**
     * @brief The movement vector (speed and direction).
     * Expressed in pixels per second.
     */
    sf::Vector2f velocity;


    /* --- Lifecycle --- */

    /**
     * @brief Construct a new Game Object.
     * Initializes velocity to (0,0).
     */
    GameObject();

    /**
     * @brief Virtual destructor.
     * Essential for a base class to ensure child classes are properly destroyed.
     */
    ~GameObject() override = default;


    /* --- Core Logic --- */

    /**
     * @brief Updates the object's logic (physics, movement).
     *
     * The default implementation applies simple movement: pos += velocity * time.
     * Can be overridden by child classes for complex behavior.
     *
     * @param deltaTime Time elapsed since the last frame (in seconds).
     */
    virtual void update(float deltaTime);

    /**
     * @brief Checks for AABB (Axis-Aligned Bounding Box) collision.
     *
     * @param other The other GameObject to test against.
     * @return true If the bounding boxes overlap.
     * @return false Otherwise.
     */
    bool checkCollision(const GameObject& other) const;

    /**
     * @brief Get the global bounding rectangle of the object.
     *
     * Pure virtual method: every child (Ball, Paddle, Brick) MUST define
     * its own physical bounds.
     *
     * @return sf::FloatRect The bounding box in global coordinates.
     */
    virtual sf::FloatRect getGlobalBounds() const = 0;
};
