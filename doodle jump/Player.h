#pragma once
#include "lib.h"

class Player
{
public:

	Player();


	void display();

	void updates(float deltaTime);
	void warp();

	//void handlecolisions();
	void draw(sf::RenderWindow& window);


	sf::RectangleShape hitbox;
	sf::Vector2f getPosition() const { return pose; }

private:


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

