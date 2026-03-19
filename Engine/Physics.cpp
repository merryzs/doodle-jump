#include "Physics.h"
#include "Collider.h"
#include "Transform.h"

void Physics::AddCollider(Collider* collider)
{
    if (collider)
        colliders.push_back(collider);
}

void Physics::RemoveCollider(Collider* collider)
{
    colliders.erase(
        std::remove(colliders.begin(), colliders.end(), collider),
        colliders.end()
    );
}

void Physics::Update(float deltaTime)
{
    for (size_t i = 0; i < colliders.size(); ++i)
    {
        for (size_t j = i + 1; j < colliders.size(); ++j)
        {
            sf::FloatRect a = colliders[i]->GetWorldBounds();
            sf::FloatRect b = colliders[j]->GetWorldBounds();

            if (a.findIntersection(b)) 
            {
                if(OnCollision)
                    OnCollision(colliders[i], colliders[j]);
            }
        }
    }
}