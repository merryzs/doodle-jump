#pragma once
#include "Component.h"
#include "Transform.h"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    GameObject();
    ~GameObject();

    Transform transform;

    void Start();
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window);
    void Destroy();

    template<typename T, typename... Args>
    T* CreateComponent(Args&&...args)
    {
        T* component = new T(std::forward<Args>(args)...);
        component->SetOwner(this);
        components.push_back(component);
        component->Start();
        return component;
    };

    template<typename T>
    T* GetComponent()
    {
        for (Component* c : components)
        {
            if (T* result = static_cast<T*>(c))
                return result;
        }
        return nullptr;
    };

    Transform& GetTransform();

private:
    std::vector<Component*> components;
};

