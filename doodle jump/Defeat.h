#pragma once
#include "lib.h"
#include "Menu.h"
#include "GameState.h"


class Defeat : public Menu
{

private:
	sf::Font font;
	sf::RectangleShape Background;
	sf::Text Text;
	sf::Text ResetText;
	sf::Text CloseText;

public:


		Defeat();

		void display() override;
		void update(sf::Vector2<float> mousePos) override;
		void draw(sf::RenderWindow& window) override;



};

