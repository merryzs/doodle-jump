#include "PowerUp.h"
#include "Player.h"

PowerUp::PowerUp(sf::Vector2f pos, PowerUpType t)
    : position(pos), type(t), active(false), collected(false), timer(0.f)
{
    size = { 50.f, 50.f };

    shape.setSize(size);
    shape.setPosition(position);

    // Couleur selon le type
    if (type == PowerUpType::JumpBoost)
    {
        shape.setFillColor(sf::Color::Red);
        duration = 0.5f;
    }
    else if (type == PowerUpType::SpeedBoost)
    {
        shape.setFillColor(sf::Color::Blue);
        duration = 5.f;
    }
    else if (type == PowerUpType::Jetpack)
    {
        shape.setFillColor(sf::Color::Yellow);
        duration = 3.f;
    }
}

void PowerUp::update(float deltaTime)
{
    if (active)
    {
        timer += deltaTime;

        if (timer >= duration)
        {
            active = false;
        }
    }

    shape.setPosition(position);
}

void PowerUp::draw(sf::RenderWindow& window)
{
    if (!collected)
        window.draw(shape);
}

void PowerUp::applyEffect(Player& player)
{
    collected = true;
    active = true;
    timer = 0.f;

    if (type == PowerUpType::JumpBoost)
    {
        player.setVelocityY(-1200.f);
    }
    else if (type == PowerUpType::SpeedBoost)
    {
        player.setSpeed(700.f);
    }
    else if (type == PowerUpType::Jetpack)
    {
        player.setGravity(500.f);
        player.setVelocityY(-800.f);
    }
}

void PowerUp::deactivateEffect(Player& player)
{
    if (type == PowerUpType::SpeedBoost)
        player.setSpeed(400.f);

    if (type == PowerUpType::Jetpack)
        player.setGravity(2000.f);
}

sf::FloatRect PowerUp::getBounds() const
{
    return shape.getGlobalBounds();
}

bool PowerUp::isCollected() const { return collected; }
bool PowerUp::isActive() const { return active; }

void PowerUp::setPosition(sf::Vector2f pos)
{
    position = pos;
    shape.setPosition(position);
}

sf::Vector2f PowerUp::getPosition() const
{
    return position;
}