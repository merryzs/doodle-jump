#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f locs, PowerUpType t)
	:loc(locs),
	lifetime(8.f)
{
	buff.setSize({ 24.f, 24.f });
	buff.setOrigin(sf::Vector2f(15.f, 15.f));
	buff.setPosition(loc);

	switch (type)
	{
	case PowerUpType::Papillon:
		
		buff.setFillColor(sf::Color::Magenta);
		break;


	case PowerUpType::Bouclier: 

		buff.setFillColor(sf::Color::Cyan);
		break;
	
	}

	buff.setOutlineThickness(3.f);
	buff.setOutlineColor(sf::Color::Green);
}

void PowerUp::update(float deltaTime) 
{
	lifetime -= deltaTime;
	buff.setPosition(loc);

}

void PowerUp::draw(sf::RenderWindow& window) 
{
}