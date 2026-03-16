#include "Wave.h"
#include "lib.h"

Wave::Wave(const sf::Texture& texture, const sf::Vector2f& startPos, const sf::Vector2f& speed)
{
    sprite.emplace(texture); 
    position = startPos;
    baseSpeed = speed;

    sprite->setPosition(position);
}

void Wave::update(float dt, float slowFactor)
{
    position += baseSpeed * slowFactor * dt;

    if (sprite.has_value())
        sprite->setPosition(position);
}

void Wave::draw(sf::RenderWindow& window) const
{
    if (sprite.has_value())
        window.draw(*sprite);
}

sf::FloatRect Wave::getHitbox() const
{
    if (sprite.has_value())
        return sprite->getGlobalBounds();

    return sf::FloatRect(); 
}

bool Wave::isOffScreen(float screenWidth) const
{
    if (!sprite.has_value())
        return false;

    return (position.x + sprite->getGlobalBounds().size.x < 0);
}