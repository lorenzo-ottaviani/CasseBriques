#pragma once
#include "GameObject.hpp"

// Represents the player's paddle.
// Inherits from GameObject to get position and collision features.
class Paddle : public GameObject {
public:
    sf::RectangleShape shape;
    float speed; // Movement speed in pixels per second

    Paddle(float startX, float startY);
    ~Paddle() override = default;

    // Checks for screen boundaries (keeps paddle inside the window)
    void update(float deltaTime) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getGlobalBounds() const override;
};
