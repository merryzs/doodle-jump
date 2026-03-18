#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f pos, EnemyType enemyType) : position(pos), type(enemyType), speed(250.f), direction(1), active(true), textureStatic("images/redMonster.png"), textureMoving("images/greenMonster.png"), spriteStat(textureStatic), spriteMove(textureMoving)
{
    spriteStat.setPosition(position);
    spriteStat.setScale({ 1.f, 1.f });

    spriteMove.setPosition(position);
    spriteMove.setScale({1.f, 1.f});

    size = sf::Vector2f(64.f, 64.f);
}

void Enemy::update(float deltaTime)
{
    if (!active)
        return;

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

        if(type == EnemyType::Static)
            spriteStat.setPosition(position);

        if(type == EnemyType::Moving)
            spriteMove.setPosition(position);
    }
}

void Enemy::draw(sf::RenderWindow& window)
{

    if (type == EnemyType::Static)
        window.draw(spriteStat);
    else if (type == EnemyType::Moving)
        window.draw(spriteMove);
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
    spriteStat.setPosition(position);
    spriteMove.setPosition(position);
}

bool Enemy::isActive() const
{
    return active;
}

void Enemy::setActive(bool value)
{
    active = value;
}