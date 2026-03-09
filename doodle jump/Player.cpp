#include "Player.h"

Player::Player() : texture("images/doodle.png"), sprite(texture)
{
    x = 250.f;
    y = 150.f;
    dy = 0;

    sprite.setPosition({ x, y });
}

void Player::update()
{
    dy += 0.2f;
    y += dy;

    sprite.setPosition({ x, y });
}

void Player::jump()
{
    dy = -10;
}

void Player::moveLeft()
{
    x -= 4;
}

void Player::moveRight()
{
    x += 4;
}

float Player::getX()
{
    return x;
}

float Player::getY()
{
    return y;
}

float Player::getDY()
{
    return dy;
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}