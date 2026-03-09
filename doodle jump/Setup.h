#pragma once
#include "Player.h"
#include "lib.h"



class Setup : public Player
{

public:

	Setup();

	virtual void setups() override;
	virtual void draw(sf::RenderWindow& window) override;



	sf::RectangleShape hitbox;


private:

	sf::Vector2f pose;

};
