#pragma once
#include "lib.h"

class Platform
{
public:
    Platform(sf::Vector2f pos, sf::Vector2f size);

    void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
    void move(const sf::Vector2f& offset);

private:
    sf::RectangleShape shape;
    sf::Texture platformTexture;
};