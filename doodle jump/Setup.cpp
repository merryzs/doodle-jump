#include "Setup.h"
#include<iostream>
Setup::Setup()
	: hitbox(),
	pose(400.f, 300.f)
{
}

void Setup::setups()
{

	//set dun carre
	
	
	hitbox.setSize({ 64.f,64.f });
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2.f);
	hitbox.setScale({ 1.f,1.f });
	std::cout << "caree";
	//set de la pose

	hitbox.setPosition({ 400.f, 300.f });

	pose = { 400.f,300.f };	


}

void Setup::draw(sf::RenderWindow& window)
{
	//draw le player
	window.draw(hitbox);
}	