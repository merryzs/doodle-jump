#pragma once
#include <SFML/Graphics.hpp>
#include "EnemyType.h"

class Enemy
{
private:
    sf::Texture textureStatic;
    sf::Texture textureMoving;
    sf::Sprite spriteStat;
    sf::Sprite spriteMove;

    sf::Vector2f position;
    sf::Vector2f size;

    EnemyType type;
    float speed;
    int direction; // -1 = gauche, 1 = droite
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
