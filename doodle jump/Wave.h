#pragma once
#include "lib.h"

class Wave
{
public:
    Wave() = default;
    Wave(sf::Texture& texture, float x, float y, const sf::Vector2f& speed);

    void update(float dt, float slowFactor);
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getHitbox() const;
    const sf::Vector2f& getPosition() const { return position; }

    bool isOffScreen(float screenHeight) const;

    void setRotation(float angle);

private:
    std::optional<sf::Sprite> sprite;

    sf::Vector2f position;
    sf::Vector2f baseSpeed;


    sf::Vector2f spriteOffset = { 0.f, 0.f };


    int currentFrame = 0;
    float frameTimer = 0.f;
    const float frameDuration = 1.f / 60.f;

};