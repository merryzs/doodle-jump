#include "Player.h"

Player::Player()
    : textureRight("images/imageB.png"),
    textureLeft("images/imageA.png"),
    sprite(textureRight)
{
    hitbox.setSize({ 64.f, 64.f });
    hitbox.setOutlineThickness(2.f);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
}

void Player::display()
{
    sprite.setTexture(textureRight);
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 64, 64 }));
    sprite.setScale({ 1.f, 1.f });
    sprite.setPosition(pose);

    hitbox.setPosition(pose);
}

void Player::updates(float deltaTime)
{
    float moveDistance = speed * deltaTime;

    
    if (!isGrabbed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            pose.x -= moveDistance;
            sprite.setTexture(textureLeft);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            pose.x += moveDistance;
            sprite.setTexture(textureRight);
        }
    }

    
    if (isOnGround())
    {
        velocityY = jumpStrength;
        isGrounded = false;
    }

    
    velocityY += gravity * deltaTime;
    pose.y += velocityY * deltaTime;

    if (isGrounded && velocityY > 0)
        velocityY = 0;

    sprite.setPosition(pose);
    hitbox.setPosition(pose);
}

void Player::warp()
{
    float Border_Left = -64.f;
    float Border_Right = 1080.f;

    if (pose.x <= Border_Left)
        pose.x = 1070;

    if (pose.x >= Border_Right)
        pose.x = -50;

    sprite.setPosition(pose);
    hitbox.setPosition(pose);
}

sf::FloatRect Player::getBounds() const
{
    return hitbox.getGlobalBounds();
}


void Player::reset()
{
    pose = { 375.f, 500.f };
    velocityY = 0;
    isGrounded = false;

    sprite.setPosition(pose);
    hitbox.setPosition(pose);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}