#include "PlatformType.h"
#include "lib.h"
#include "Random.h"


PlatformType randomPlatformType()
{
    static std::uniform_int_distribution<int> percentDist(0, 99);
    int p = percentDist(rng);

    if (p < 60) return PlatformType::Normal;// 60
    else if (p < 85) return PlatformType::Moving;// 25
    else if (p < 95) return PlatformType::Bouncy;// 10
    else return PlatformType::Breakable; // 5
}

sf::Color colorFromType(PlatformType type)
{
    switch (type)
    {
    case PlatformType::Normal:
        return sf::Color::Cyan;
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