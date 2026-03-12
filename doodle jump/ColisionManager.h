#pragma once
#include "Player.h"
#include "Platform.h"
#include "lib.h"

class CollisionManager
{
public:
    void handle(Player& player, const std::vector<Platform>& platforms);
};