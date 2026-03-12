#include "Player.h"

Player::Player() : playerTexture("images/doodle.png"), playerSprite(playerTexture)
{
    x = 50.f;
    y = 150.f;
    dy = 0;

    playerSprite.setPosition({ x, y });
}

void Player::update()
{
    dy += 0.2f;
    y += dy;

    if (x > 500.f) x = 0.f;
    if (x < -60.f) x = 550.f - playerTexture.getSize().x;

    playerSprite.setPosition({ x, y });
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

bool Player::checkCollisions(const Platform& plats)
{
    sf::Vector2f platformpos = plats.getPosition();
    sf::Vector2f platsize(68.f, 14.f);

    float playerLeft = x + 20.f;
    float playerRight = x + 60.f;
    float playerBottom = y + 70.f;

    if (playerBottom > platformpos.y &&
        playerBottom < platformpos.y + platsize.y &&
        playerRight > platformpos.x &&
        playerLeft < platformpos.x + platsize.x &&
        dy > 0)
    {
        return true;
    }
    return false;
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(playerSprite);
}