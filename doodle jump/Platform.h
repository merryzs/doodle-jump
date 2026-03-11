#pragma once
#include <SFML/Graphics.hpp>
#include "PlatformType.h"

class Platform
{
public:
    Platform(sf::Vector2f position, sf::Vector2f size, PlatformType type);
    
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    void move(const sf::Vector2f& offset);
    void breakPlatform();
    
private:
	PlatformType type;
    sf::RectangleShape shape;
    bool isBroken = false;
};