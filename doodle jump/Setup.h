#pragma once
#include "Player.h"
#include "lib.h"



class Setup : public Player
{

public:

	Setup();

	virtual void setup() override;



	sf::RectangleShape m_playerShape;


private:

	sf::Vector2f pose;

};
