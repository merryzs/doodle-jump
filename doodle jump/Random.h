#pragma once
#include "lib.h"

// Constantes — inline pour éviter les redéfinitions
inline constexpr float screen_width = 1080.f;
inline constexpr float screen_height = 1080.f;

// Générateur aléatoire partagé
inline std::mt19937 rng{ std::random_device{}() };
inline std::uniform_int_distribution<int> sideDist(0, 1);

// Fonction — inline obligatoire dans un header
inline float randomPlatformX(float platformWidth)
{
    float halfScreen = screen_width / 2.f;
    if (sideDist(rng) == 0)
    {
        std::uniform_real_distribution<float> dist(0.f, halfScreen - platformWidth);
        return dist(rng);
    }
    else
    {
        std::uniform_real_distribution<float> dist(halfScreen, screen_width - platformWidth);
        return dist(rng);
    }
}

inline float RandomXWave(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}