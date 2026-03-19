#include "CollisionManager.h"
#include "Player.h"
#include "Platform.h"

void CollisionManager::handle(Player& player, std::vector<Platform>& platforms)
{
    sf::Vector2f pPos = player.hitbox.getPosition();
    sf::Vector2f pSize = player.hitbox.getSize();
    sf::FloatRect playerRect(pPos, pSize);

    player.setGrounded(false);

    for (auto& platform : platforms)
    {
        sf::Vector2f platPos = platform.getPosition();
        sf::Vector2f platSize = platform.getSize();
        sf::FloatRect platRect(platPos, platSize);

        if (auto inter = playerRect.findIntersection(platRect))
        {
            
            if (inter->size.y < inter->size.x && player.getVelocityY() > 0.f)
            {
                
                if (platform.getType() == PlatformType::Breakable)
                {
                    platform.breakPlatform();
                    continue;
                }

                
                if (platform.getType() == PlatformType::Bouncy)
                {
                    player.setVelocityY(-1200.f);
                    platform.triggerBounce();
                    continue;
                }

                
                player.setPose({
                    pPos.x,
                    platRect.position.y - pSize.y
                    });

                player.setVelocityY(0.f);
                player.setGrounded(true);

                pPos = player.getPose();
                playerRect = sf::FloatRect(pPos, pSize);
            }
        }
    }
}

