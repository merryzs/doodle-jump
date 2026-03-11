#pragma once
#include "lib.h"

class Player
{
private:

    sf::Texture playerTexture;

    float x;
    float y;
    float dy;

public:

    Player();    sf::Sprite playerSprite;

    void update();
    void jump();

    void moveLeft();
    void moveRight();

    float getX();
    float getY();
    float getDY();

    void draw(sf::RenderWindow& window);
};

