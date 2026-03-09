#pragma once
#include "Player.h"
#include "lib.h"



class Setup : public Player
{

public:

	Setup();

	virtual void setup() override;


private:

	sf::RectangleShape m_playerShape;


};
