#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f pos, EnemyType enemyType) 
    : position(pos), 
    type(enemyType), 
    speed(250.f), 
    direction(1), 
    active(true),  
    StaticMobSprite(StaticMob), 
    MoveMobSprite(MoveMob)
{ 

    if (!StaticMob.loadFromFile("images/redMonster.png"))
        std::cerr << "Erreur: redMonster.png introuvable\n";
    if (!MoveMob.loadFromFile("images/greenMonster.png"))
        std::cerr << "Erreur: greenMonster.png introuvable\n";


    StaticMobSprite.setPosition(position);
    StaticMobSprite.setScale({ 1.f, 1.f });

    MoveMobSprite.setPosition(position);
    MoveMobSprite.setScale({ 1.f, 1.f });

    size = sf::Vector2f(64.f, 64.f);
}

void Enemy::update(float deltaTime)
{
    if (!active)
    {
        return;
    }


    if (type == EnemyType::Moving)
    {
        position.x += direction * speed * deltaTime;

        if (position.x <= 0.f)
        {
            position.x = 0.f;
            direction = 1;
        }

        if (position.x + size.x >= 1080.f)
        {
            position.x = 1080.f - size.x;
            direction = -1;
        }

    }
    
    StaticMobSprite.setPosition(position);
    MoveMobSprite.setPosition(position);
}

void Enemy::draw(sf::RenderWindow& window)
{

    if (type == EnemyType::Static)
        window.draw(StaticMobSprite);
    else if (type == EnemyType::Moving)
        window.draw(MoveMobSprite);
}

sf::Vector2f Enemy::getPosition() const
{
    return position;
}

sf::Vector2f Enemy::getSize() const
{
    return size;
}

sf::FloatRect Enemy::getBounds() const
{
    return sf::FloatRect(position, size);
}

EnemyType Enemy::getType() const
{
    return type;
}

void Enemy::setPosition(sf::Vector2f newPos)
{
    position = newPos;
    StaticMobSprite.setPosition(position);
    MoveMobSprite.setPosition(position);
}

bool Enemy::isActive() const
{
    return active;
}

void Enemy::setActive(bool value)
{
    active = value;
}