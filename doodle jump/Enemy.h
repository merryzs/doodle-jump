#pragma once
#include "lib.h"

enum class EnemyType
{
    Static,
    Moving
};

class Enemy
{
private:
    sf::Texture StaticMob;
    sf::Sprite StaticMobSprite;

    sf::Texture MoveMob;
    sf::Sprite MoveMobSprite;


    sf::Vector2f position;
    sf::Vector2f size;

    EnemyType type;
    float speed;
    int direction;
    bool active;

public:
    Enemy(sf::Vector2f pos, EnemyType enemyType);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    sf::FloatRect getBounds() const;
    EnemyType getType() const;

    void setPosition(sf::Vector2f newPos);


    bool isActive() const;
    void setActive(bool value);
};