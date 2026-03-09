#pragma once
#include "lib.h"
#include "Player.h"	

class update : public Player
{
public:
		update();
		virtual void updates(float deltaTime) override;

private:


};

