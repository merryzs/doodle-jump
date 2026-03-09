#include "Platform.h"

Platform::Platform(sf::Vector2f position, sf::Vector2f size)
{
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(sf::Color(120, 120, 120));
}

void Platform::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}

sf::Vector2f Platform::getPosition() const
{
    return shape.getPosition();
}

void Platform::move(const sf::Vector2f& offset)
{
    shape.move(offset);
}
