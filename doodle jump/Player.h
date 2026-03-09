#pragma once
#include "lib.h"

class Player
{
public:

	Player();

	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow& window);
	virtual void setup();

private:


};

