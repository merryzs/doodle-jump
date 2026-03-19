#pragma once
#include "lib.h"
#include "GameState.h"
#include "Menu.h"


class WinMenu : public Menu
{
	
private:

	sf::Font font;
	sf::RectangleShape Background;
	sf::Text Text;

public:

	WinMenu();

	void display() override;
	void update(sf::Vector2f mousePose) override;
	void draw(sf::RenderWindow& window) override;

};

