#pragma once

/* ===  INCLUDES  === */

// --- Parent Class ---
#include "GameObject.hpp"


/* ===   CLASS DEFINITION   === */

/**
 * @brief Represents the player's paddle.
 *
 * The paddle is controlled by the user via the InputManager.
 * It inherits from GameObject for position and collision management.
 */
class Paddle : public GameObject {
public:
    /* --- Public Members --- */

    /**
     * @brief The visual representation of the paddle.
     */
    sf::RectangleShape shape;

    /**
     * @brief Movement speed in pixels per second.
     */
    float speed;


    /* --- Lifecycle --- */

    /**
     * @brief Construct a new Paddle object.
     *
     * Sets dimensions (100x20), color (Cyan), and centers the origin.
     * @param startX Initial X position (center).
     * @param startY Initial Y position (center).
     */
    Paddle(float startX, float startY);

    /**
     * @brief Destroy the Paddle object.
     */
    ~Paddle() override = default;


    /* --- Core Logic --- */

    /**
     * @brief Constraints the paddle within the window boundaries.
     *
     * Note: Actual movement is handled by the InputManager in Game.cpp.
     * This method ensures the paddle doesn't leave the screen (Clamping).
     *
     * @param deltaTime Time elapsed since the last frame.
     */
    void update(float deltaTime) override;


    /* --- Graphics --- */

    /**
     * @brief Draws the paddle to the render target.
     * @param target The window to draw on.
     * @param states Current render states.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Gets the global bounding box of the paddle.
     * @return sf::FloatRect The bounding rectangle in world coordinates.
     */
    sf::FloatRect getGlobalBounds() const override;
};
