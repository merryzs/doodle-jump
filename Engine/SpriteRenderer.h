#pragma once
#include "Component.h"

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(const std::filesystem::path& path);

	void LoadSprite(const std::filesystem::path& path, int frameWidth, int frameHeight);
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow& window) override;

private:
	sf::Texture texture;
	sf::Sprite sprite;

	// Animation
	int frameWidth = 64;
	int frameHeight = 64;
	int currentFrame = 0;
	int frameCount = 1;
	float frameTime = 0.08f; // 0.08f pour 80 ms
	float timer = 0.f;
};