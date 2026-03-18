#pragma once
#include "lib.h"

enum class PowerUpType
{
    JumpBoost,
    SpeedBoost,
    Jetpack,
    Shield
};

class PowerUp
{
private:
    sf::Vector2f position;
    sf::Vector2f size;

    PowerUpType type;
    bool active;
    bool collected;

    float duration;
    float timer;

    sf::RectangleShape shape;

public:
    PowerUp(sf::Vector2f pos, PowerUpType type);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    void applyEffect(class Player& player);
    void deactivateEffect(class Player& player);

    sf::FloatRect getBounds() const;

    bool isCollected() const;
    bool isActive() const;

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;
};
