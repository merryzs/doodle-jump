#pragma once
#include "lib.h"
#include "PlatformType.h"

class Platform
{
public:

    static std::optional<sf::Texture> normalTex;
    static std::optional<sf::Texture> movingTex;
    static std::optional<sf::Texture> bouncyTex;
    static std::vector <std::optional<sf::Texture>> breakableTex;

    Platform(sf::Vector2f position, sf::Vector2f size, PlatformType type);

    void draw(sf::RenderWindow& window) const;
    void update(float deltatime);

    sf::Vector2f getPosition() const;
    void move(const sf::Vector2f& offset);
    void breakPlatform();

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

    PlatformType getType() const { return type; }
    void triggerBounce() { bounceTimer = 0.3f; }    

    void setPosition(const sf::Vector2f& pos) {
        sprite.setPosition(pos);
    }

    void SetTexture(PlatformType type, int frame = 0);
    

    static void loadTexture();

private:
    float bounceTimer = 0.f;
    float speed = 100.f;

    int direction = 1;
    float fallSpeed = 0.f;

    PlatformType type;
    sf::Vector2f size;
    sf::Sprite sprite;

    bool isBroken = false;
    float breakTimer = 0.f;
    int currentBreakFrame = 0;
};