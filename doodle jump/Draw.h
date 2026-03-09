#pragma once
#include "lib.h"
#include "Player.h"
#include "Setup.h"

class Draw : public Player
{

public:
	Draw();
	virtual void draw(sf::RenderWindow& window) override;

private:



};

