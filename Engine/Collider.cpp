#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"

sf::FloatRect Collider::GetWorldBounds() const
{
    if (!owner) return localBounds;

    Transform transform = owner->GetTransform();

    return sf::FloatRect(transform.position, transform.size);
}