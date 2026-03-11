#pragma once
#include <SFML/Graphics.hpp>
#include <random>

enum class PlatformType
{
	Normal,
	Moving,
	Breakable,
	Bouncy,
};

PlatformType randomPlatformType();
sf::Color colorFromType(PlatformType type);

extern std::mt19937 rng;
extern std::uniform_int_distribution<int> sideDist;

