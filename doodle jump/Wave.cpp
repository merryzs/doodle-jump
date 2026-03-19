#include "Wave.h"
#include "lib.h"


static constexpr int Frame_width = 64;
static constexpr int Frame_height = 64;
static constexpr int Frame_cols = 4;
static constexpr int Frame_rows = 4;
static constexpr int Frame_count = 4;
static constexpr float Frame_duration = 1.f / 60.f;

Wave::Wave(sf::Texture& texture, float x, float y, const sf::Vector2f& speed)
{
    const_cast<sf::Texture&>(texture).setSmooth(false);

    sprite.emplace(texture);

    position = { x, y };
    baseSpeed = speed;

    sprite->setTextureRect(sf::Rect<int>(
        sf::Vector2i(0, 0),
        sf::Vector2i(Frame_width, Frame_height)
    ));

    sprite->setOrigin({ Frame_width / 2.f, Frame_height / 2.f });
    sprite->setScale({ 3.f, 3.f });

    spriteOffset = sf::Vector2f(0.f, 0.f);

    sprite->setPosition(position + spriteOffset);
}

void Wave::update(float dt, float slowFactor)
{
    position += baseSpeed * slowFactor * dt;

    frameTimer += dt;
    if (frameTimer >= Frame_duration)
    {
        frameTimer = 0.f;
        currentFrame = (currentFrame + 1) % Frame_count;

        int col = currentFrame % Frame_cols;
        int row = currentFrame / Frame_cols;

        sprite->setTextureRect(sf::Rect<int>(
            sf::Vector2i(col * Frame_width, row * Frame_height),
            sf::Vector2i(Frame_width, Frame_height)
        ));
    }

    sprite->setPosition(position + spriteOffset);
}

void Wave::draw(sf::RenderWindow& window) const
{
    if (sprite.has_value())
        window.draw(*sprite);
}

sf::FloatRect Wave::getHitbox() const
{
    if (!sprite.has_value())
        return sf::FloatRect();

    float w = Frame_width * sprite->getScale().x;
    float h = Frame_height * sprite->getScale().y;

    float x = sprite->getPosition().x - w * 0.5f;
    float y = sprite->getPosition().y - h * 0.5f;

    float reducedW = w * 0.6f;
    float reducedH = h * 0.6f;

    float offsetX = (w - reducedW) * 0.5f;
    float offsetY = (h - reducedH) * 0.5f;

    return sf::Rect<float>(
        sf::Vector2f(x + offsetX, y + offsetY),
        sf::Vector2f(reducedW, reducedH)
    );
}

bool Wave::isOffScreen(float screenHeight) const
{
    return position.y > screenHeight;
}

void Wave::setRotation(float angle)
{
    if (sprite.has_value())
        sprite->setRotation(sf::degrees(angle));
}