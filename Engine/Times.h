#pragma once

#include <SFML/System.hpp>

class Times
{
public:
    static void Update();
    static float DeltaTime();

private:
    static sf::Clock clock;
    static float deltaTime;
};