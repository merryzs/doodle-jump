#include "Random.h"

const float screen_width = 1080.f;
const float screen_height = 1080.f;

static std::mt19937 rng(std::random_device{}());
static std::uniform_int_distribution<int> sideDist(0, 1);

float randomPlatformX(float platformWidth)
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

float RandomXWave(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}