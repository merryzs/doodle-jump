#include "PlatformType.h"
#include "lib.h"


std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> sideDist(0, 1);

PlatformType randomPlatformType()
{
    static std::uniform_int_distribution<int> percentDist(0, 99);
    int p = percentDist(rng);

    if (p < 60) return PlatformType::Normal;// 60
    else if (p < 85) return PlatformType::Breakable;// 25
    else if (p < 95) return PlatformType::Moving;// 10
    else return PlatformType::Bouncy; // 5
}

sf::Color colorFromType(PlatformType type)
{
    switch (type)
    {
    case PlatformType::Normal:
        return sf::Color::White;
    case PlatformType::Moving:
        return sf::Color::Blue;
    case PlatformType::Breakable:
        return sf::Color::Red;
    case PlatformType::Bouncy:
        return sf::Color::Green;
    default:
        return sf::Color::White;
    }
}