#include "Platform.h"
#include "PlatformType.h"

std::optional<sf::Texture> Platform::normalTex;
std::optional<sf::Texture> Platform::movingTex;
std::optional<sf::Texture> Platform::bouncyTex;
std::vector <std::optional<sf::Texture>> Platform::breakableTex;


Platform::Platform(sf::Vector2f position, sf::Vector2f size, PlatformType type) : type(type), sprite(normalTex.value())
{
    SetTexture(type);
    sprite.setPosition(position);
    sprite.setScale({ (float)size.x / 64.f, (float)size.y / 16.f });
}

void Platform::breakPlatform()
{
    if (type == PlatformType::Breakable && !isBroken)
    {
        isBroken = true;
        breakTimer = 0.f;
        currentBreakFrame = 0;
    }
}

void Platform::SetTexture(PlatformType type, int frame)
{
    switch (type)
    {
    case PlatformType::Normal:
        sprite.setTexture(normalTex.value(), true);
        break;
    case PlatformType::Moving:
        sprite.setTexture(movingTex.value(), true);
        break;
    case PlatformType::Bouncy:
        sprite.setTexture(bouncyTex.value(), true);
        break;
    case PlatformType::Breakable:
        sprite.setTexture(breakableTex[frame].value(), true);
        break;
    }
}

void Platform::loadTexture()
{
    normalTex.emplace("images/os1.png");
    movingTex.emplace("images/os3.png");
    bouncyTex.emplace("images/nuage1.png");

    for (int i = 0; i < 3; ++i)
    {
        breakableTex.emplace_back("images/os_casse_gris" + std::to_string(i + 1) + ".png");
    }
}

void Platform::draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

sf::Vector2f Platform::getPosition() const
{
    return sprite.getPosition();
}

void Platform::update(float dt)
{
     if (isBroken)
    {
        breakTimer += dt;
        if (breakTimer >= 0.2f && currentBreakFrame < 2)
        {
            currentBreakFrame++;
            SetTexture(PlatformType::Breakable, currentBreakFrame);
            breakTimer = 0.f;
        }

        sprite.move({ 0.f, 500.f * dt });
        return;
    }

    switch (type)
    {
        case PlatformType::Moving:
            sprite.move({ speed * direction * dt, 0.f });
            if (sprite.getPosition().x < 0.f) direction = 1;
            if (sprite.getPosition().x + size.x > 1080.f) direction = -1;
            break;

        case PlatformType::Bouncy:
            if (bounceTimer > 0.f)
            {
                bounceTimer -= dt;
                float scale = 1.f + std::sin(bounceTimer * 20.f) * 0.2f;
                sprite.setScale({ 1.f, scale });
            }
            else
            {
                sprite.setScale({ 1.f, 1.f });
            }
            break;

        default: break;
    }
}

void Platform::move(const sf::Vector2f& offset)
{
    sprite.move(offset);
}