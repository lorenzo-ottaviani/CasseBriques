#pragma once

/* ===  INCLUDES  === */

// --- Parent Class ---
#include "GameObject.hpp"


/* ===   CLASS DEFINITION   === */

/**
 * @brief Represents a destroyable brick in the game level.
 *
 * Bricks are static objects that the ball can collide with.
 * They have a destroyed state which prevents them from being drawn or hit again.
 */
class Brick : public GameObject {
public:
    /* --- Public Members --- */

    /**
     * @brief The visual representation of the brick.
     */
    sf::RectangleShape shape;

    /**
     * @brief State flag.
     * If true, the brick is considered broken, ignored by collisions, and not drawn.
     */
    bool isDestroyed = false;


    /* --- Lifecycle --- */

    /**
     * @brief Construct a new Brick object.
     *
     * Sets dimensions (60x20), color (Yellow), and centers the origin.
     * @param x Initial X position (center).
     * @param y Initial Y position (center).
     */
    Brick(float x, float y);

    /**
     * @brief Destroy the Brick object.
     */
    ~Brick() override = default;


    /* --- Core Logic --- */

    /**
     * @brief Updates the brick logic.
     *
     * Currently empty as bricks are static, but could handle animations in the future.
     * @param deltaTime Time elapsed since the last frame.
     */
    void update(float deltaTime) override;


    /* --- Graphics --- */

    /**
     * @brief Draws the brick if it is not destroyed.
     * @param target The window to draw on.
     * @param states Current render states.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Gets the global bounding box of the brick.
     * @return sf::FloatRect The bounding rectangle in world coordinates.
     */
    sf::FloatRect getGlobalBounds() const override;
};
