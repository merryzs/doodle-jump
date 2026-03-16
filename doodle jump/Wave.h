#pragma once
#include "lib.h"

class Wave
{
public:
    Wave() = default; 
    Wave(const sf::Texture& texture, const sf::Vector2f& startPos, const sf::Vector2f& speed);

    void update(float dt, float slowFactor);
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getHitbox() const;
    const sf::Vector2f& getPosition() const { return position; }

    bool isOffScreen(float screenWidth) const;

private:
    std::optional<sf::Sprite> sprite;
    sf::Vector2f position;
    sf::Vector2f baseSpeed;
};