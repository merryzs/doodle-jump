#include "Times.h"

sf::Clock Times::clock;
float Times::deltaTime = 0.f;

void Times::Update()
{
    deltaTime = clock.restart().asSeconds();
}

float Times::DeltaTime()
{
    return deltaTime;
}
