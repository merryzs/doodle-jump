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
        
        fallSpeed += 500.f * dt;
        shape.move({ 0, fallSpeed * dt });
        return;
    }

    switch (type)
    {
    case PlatformType::Moving:
    {
        shape.move({ speed * direction * dt, 0 });

        
        if (shape.getPosition().x < 0)
            direction = 1;
        if (shape.getPosition().x + shape.getSize().x > 1080)
            direction = -1;

        break;
    }

    case PlatformType::Bouncy:
    {
        
        if (bounceTimer > 0)
        {
            bounceTimer -= dt;
            float scale = 1.f + std::sin(bounceTimer * 20.f) * 0.2f;
            shape.setScale({ 1.f, scale });
        }
        else
        {
            shape.setScale({ 1.f, 1.f });
        }
        break;
    }

    default:
        break;
    }
}

void Platform::move(const sf::Vector2f& offset)
{
    shape.move(offset);
}