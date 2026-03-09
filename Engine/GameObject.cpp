#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
    CreateComponent<Transform>();
}

GameObject::~GameObject()
{
    for (Component* c : components)
        delete c;
}

void GameObject::Start()
{
    for (Component* c : components)
        c->Start();
}

void GameObject::Update(float dt)
{
    for (Component* c : components)
        c->Update(dt);
}

void GameObject::Render(sf::RenderWindow& window)
{
    for (Component* c : components)
        c->Render(window);
}

void GameObject::Destroy()
{
    for (Component* c : components)
        c->Destroy();
}

Transform& GameObject::GetTransform()
{
    return transform;
}