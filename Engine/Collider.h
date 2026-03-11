#pragma once
#include "Component.h"
#include <SFML/Graphics/Rect.hpp>

class Collider : public Component
{
public:
    Collider() = default;
    Collider(const sf::Vector2f& position, const sf::Vector2f& size)
    {
        localBounds.position = position;
        localBounds.size = size;
    }

    sf::FloatRect GetWorldBounds() const;

    void SetLocalBounds(const sf::FloatRect& bounds) { localBounds = bounds; }
    const sf::FloatRect& GetLocalBounds() const { return localBounds; }

    void SetOwner(GameObject* obj) { owner = obj; }
	GameObject* GetOwner() const { return owner; }

private:

    sf::FloatRect localBounds;
};

