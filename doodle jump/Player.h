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


	sf::RectangleShape hitbox;
	sf::Vector2f getPosition() const { return pose; }

	sf::Vector2f getPose() const { return pose; }
	void setPose(const sf::Vector2f& p) { pose = p; hitbox.setPosition(p); sprite.setPosition(p); }
	sf::FloatRect getBounds() const;
	float getVelocityY() const { return velocityY; }
	void setVelocityY(float v) { velocityY = v; }

	void setGrounded(bool g) { isGrounded = g; }
	
	void setSpeed(float s);
	void setGravity(float g);

	float getSpeed() const;
	float getGravity() const;

private:


	float speed = 500.f;

	sf::Vector2f pose;

	sf::Texture texture;
	sf::Sprite sprite;

	//jump test
	float velocityY = 0.f;
	bool isGrounded = false;
	float gravity = 1500.f;
	const float jumpStrength = -1000.f;
	float groundLevel = 700.f;

	float Border_left = -64.f;
	float Border_Right = 750.f;

};

