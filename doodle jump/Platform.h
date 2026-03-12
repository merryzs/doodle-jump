#pragma once
#include <SFML/Graphics.hpp>
#include "PlatformType.h"

class Platform
{
public:
    Platform(sf::Vector2f position, sf::Vector2f size, PlatformType type);

    void draw(sf::RenderWindow& window) const;
    void update(float deltatime);

    sf::Vector2f getPosition() const;
    void move(const sf::Vector2f& offset);
    void breakPlatform();

    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    PlatformType getType() const { return type; }
    void triggerBounce() { bounceTimer = 0.3f; }

    sf::Vector2f getSize() const { return shape.getSize(); }

private:
    float bounceTimer = 0.f;
    float speed = 100.f;
    int direction = 1;
    float fallSpeed = 0.f;
    PlatformType type;
    sf::RectangleShape shape;
    bool isBroken = false;
};