#pragma once
#include "lib.h"
#include "Platform.h"

class Player
{
private:

    sf::Texture playerTexture;

    float x;
    float y;
    float dy;

    const int PLAYER_LEFT_BOUNDING_BOX = 20;
    const int PLAYER_RIGHT_BOUNDING_BOX = 60;
    const int PLAYER_BOTTOM_BOUNDING_BOX = 70;

public:

    Player();    sf::Sprite playerSprite;

    void update();
    void jump();

    void moveLeft();
    void moveRight();

    float getX();
    float getY();
    float getDY();

    void setY(float newY) { y = newY; playerSprite.setPosition({ x, y }); }
    void setX(float newX) { x = newX; playerSprite.setPosition({ x, y }); }

    bool checkCollisions(const Platform& plats);

    void draw(sf::RenderWindow& window);
};

