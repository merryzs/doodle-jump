#pragma once
#include "lib.h"

class Player
{
private:

    sf::Sprite sprite;
    sf::Texture texture;

    float x;
    float y;
    float dy;

public:

    Player();

    void update();
    void jump();

    void moveLeft();
    void moveRight();

    float getX();
    float getY();
    float getDY();

    void draw(sf::RenderWindow& window);
};

