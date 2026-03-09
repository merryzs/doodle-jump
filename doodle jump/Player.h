#pragma once
#include "lib.h"

class Player
{
public:

	Player();


	void display();

	void updates(float deltaTime);
	//void handlecolisions();
	void draw(sf::RenderWindow& window);

	
	sf::RectangleShape hitbox;
	sf::Vector2f getPosition() const { return pose; }

private:


	float speed = 500.f;

	sf::Vector2f pose;

};

