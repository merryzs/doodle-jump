#pragma once
#include "lib.h"

class Player
{
public:

	Player();

	virtual void updates(float deltaTime);
	virtual void draw(sf::RenderWindow& window);
	virtual void setups();
	

private:


};

