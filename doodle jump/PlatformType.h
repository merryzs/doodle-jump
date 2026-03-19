#pragma once
#include "lib.h"
#include "Random.h" 

enum class PlatformType
{
    Normal,
    Moving,
    Breakable,
    Bouncy,
};

PlatformType randomPlatformType();
sf::Color colorFromType(PlatformType type);
