#pragma once

/* ===  INCLUDES  === */

// --- Parent Class ---
#include "GameObject.hpp"


/* ===   CLASS DEFINITION   === */

/**
 * @brief Represents the ball in the game.
 *
 * The ball moves automatically based on its velocity and bounces off the window walls.
 * It inherits from GameObject for movement and rendering capabilities.
 */
class Ball : public GameObject {
public:
    /* --- Public Members --- */

    /**
     * @brief The visual representation of the ball.
     */
    sf::CircleShape shape;


    /* --- Lifecycle --- */

    /**
     * @brief Construct a new Ball object.
     *
     * Sets up the shape (radius, color, origin) and initial velocity.
     * @param startX Initial X position (center of the ball).
     * @param startY Initial Y position (center of the ball).
     */
    Ball(float startX, float startY);

    /**
     * @brief Destroy the Ball object.
     */
    ~Ball() override = default;


    /* --- Core Logic --- */

    /**
     * @brief Updates the ball's position and handles wall collisions.
     *
     * 1. Moves the ball based on current velocity.
     * 2. Checks if the ball hits the Left, Right, or Top screen edges.
     * 3. Bounces (inverts velocity) and corrects position if a collision occurs.
     *
     * @param deltaTime Time elapsed since the last frame.
     */
    void update(float deltaTime) override;


    /* --- Graphics --- */

    /**
     * @brief Draws the ball to the render target.
     * @param target The window to draw on.
     * @param states Current render states (transformations).
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Gets the global bounding box of the ball.
     * Used for collision detection with the Paddle and Bricks.
     * @return sf::FloatRect The bounding rectangle.
     */
    sf::FloatRect getGlobalBounds() const override;
};
