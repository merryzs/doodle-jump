#include "GameObject.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include <iostream>

SpriteRenderer::SpriteRenderer(const std::filesystem::path& path):sprite(texture)
{
    //sprite.setTexture(texture, true);
    LoadSprite(path, frameWidth, frameHeight);
};

void SpriteRenderer::LoadSprite(const std::filesystem::path& path, int fw, int fh)
{
    if (!texture.loadFromFile(path))
    {
        std::cout << "Can't load " << path << std::endl;
        return;
    }

    frameWidth = fw;
    frameHeight = fh;

	texture.setSmooth(true);
    sprite.setTexture(texture, true);
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { fw, fh }));
}

void SpriteRenderer::Update(float deltaTime)
{
    Transform& transform = owner->GetTransform();        
    sprite.setPosition(transform.position);    
    sprite.setRotation(sf::degrees (transform.rotation));    
    sprite.setScale(transform.scale);
}

void SpriteRenderer::Render(sf::RenderWindow& window)
{
    window.draw(sprite);
}
