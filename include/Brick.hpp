#pragma once
#include "GameObject.hpp"

class Brick : public GameObject {
public:
    sf::RectangleShape shape;
    bool isDestroyed = false; // Flag to check if the brick is broken

    Brick(float x, float y);
    ~Brick() override = default;

    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getGlobalBounds() const override;
};
