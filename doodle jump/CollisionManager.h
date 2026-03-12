#pragma once
#include "Player.h"
#include "Platform.h"


class CollisionManager
{
	public:
		void handle(Player& player, std::vector<Platform>& platforms);
};

