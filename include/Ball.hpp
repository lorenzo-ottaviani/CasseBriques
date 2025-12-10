#pragma once
#include "GameObject.hpp"

class Ball : public GameObject {
public:
    sf::CircleShape shape;

    Ball(float startX, float startY);
    ~Ball() override = default;

    // Handles movement and bouncing off walls
    void update(float deltaTime) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getGlobalBounds() const override;
};
