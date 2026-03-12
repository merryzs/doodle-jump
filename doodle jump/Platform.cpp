#include "Platform.h"
#include "PlatformType.h"

Platform::Platform(sf::Vector2f position, sf::Vector2f size, PlatformType type)
    :type(type)
{

    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(colorFromType(type));
}

void Platform::breakPlatform()
{
    if (type == PlatformType::Breakable && !isBroken)
    {
        isBroken = true;
        fallSpeed = 1500.f;
        shape.setFillColor(sf::Color(128, 0, 0));
    }
}

void Platform::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}

sf::Vector2f Platform::getPosition() const
{
    return shape.getPosition();
}

void Platform::update(float dt)
{
    if (isBroken)
    {
        shape.move({ 0.f, fallSpeed * dt });
    }
    if (type == PlatformType::Moving)
    {
        shape.move({ speed * direction * dt, 0.f });

        if (shape.getPosition().x < 0 ||
            shape.getPosition().x + shape.getSize().x > 400)
        {
            direction *= -1;
        }
    }
    if (type == PlatformType::Bouncy)
    {
        bounceTimer += dt;
        float scale = 1.f + 0.05f * std::sin(bounceTimer * 10.f);
        shape.setScale({ scale, 1.f });
    }
}

void Platform::move(const sf::Vector2f& offset)
{
    shape.move(offset);
}