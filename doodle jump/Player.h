#pragma once
#include "lib.h"

class Player
{
public:
    Player();

    void display();
    void updates(float deltaTime);
    void warp();
    void reset();
    void draw(sf::RenderWindow& window);

    
    const sf::Vector2f& getPose() const { return pose; }
    void setPose(const sf::Vector2f& p) { pose = p; sprite.setPosition(p); hitbox.setPosition(p); }

    float getVelocityY() const { return velocityY; }
    void setVelocityY(float v) { velocityY = v; }

    void setGrounded(bool g) { isGrounded = g; }
    bool isOnGround() const { return isGrounded && !isGrabbed; }

    sf::FloatRect getHitbox() const { return hitbox.getGlobalBounds(); }

  
    bool isGrabbed = false;
    sf::Vector2f grabOffset;

    float resistance = 0.f;
    float resistanceMax = 200.f;
    float slowFactor = 0.5f;

  
    sf::RectangleShape hitbox;

   

private:
    sf::Texture textureRight;
    sf::Texture textureLeft;

    sf::Sprite sprite;

    sf::Vector2f pose = { 375.f, 500.f };
    float speed = 300.f;
    float gravity = 1500.f;
    float jumpStrength = -1000.f;
    float velocityY = 0.f;

    bool isGrounded = false;
};