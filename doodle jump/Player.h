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


	void display();

	void updates(float deltaTime);
	void warp();
	
	//void handlecolisions();
	void draw(sf::RenderWindow& window);

	
	sf::RectangleShape hitbox;
	sf::Vector2f getPosition() const { return pose; }

    void moveLeft();
    void moveRight();

    float getX();
    float getY();
    float getDY();

    void setY(float newY) { y = newY; playerSprite.setPosition({ x, y }); }
    void setX(float newX) { x = newX; playerSprite.setPosition({ x, y }); }

    bool checkCollisions(const Platform& plats);

	float speed = 500.f;

	sf::Vector2f pose;

	sf::Texture texture;
	sf::Sprite sprite;

	//jump test
	float velocityY = 0.f;
	bool isGrounded = false;
	const float gravity = 1500.f;
	const float jumpStrength = -1000.f;
	float groundLevel = 700.f;


	float Border_left = -64.f;
	float Border_Right = 750.f;

};

