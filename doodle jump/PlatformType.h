#pragma once
#include "lib.h"


enum class PlatformType
{
	Normal,
	Moving,
	Breakable,
	Bouncy,
};

PlatformType randomPlatformType();

extern std::mt19937 rng;
extern std::uniform_int_distribution<int> sideDist;