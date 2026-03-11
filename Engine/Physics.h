#pragma once
#include <vector>
#include <functional>

class Collider;

class Physics
{
public:
    
    void AddCollider(Collider* collider);

    void RemoveCollider(Collider* collider);

    void Update(float deltaTime);

    std::function<void(Collider* coll1, Collider* coll2)> OnCollision;

private:
    std::vector<Collider*> colliders;

};

