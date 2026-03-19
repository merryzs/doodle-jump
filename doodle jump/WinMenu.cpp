#include "WinMenu.h"

WinMenu::WinMenu()
	:Text(font)

{



	{
		if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
			std::cerr << "Impossible de charger la police\n";

		Background.setSize({ 1080 , 1080 });
		Background.setFillColor(sf::Color::Black);


		Text.setString("GG WP");
		Text.setCharacterSize(80);
		Text.setPosition({ 300,300 });
		Text.setFillColor(sf::Color::Red);


	}
}

void WinMenu::display()
{
}

void WinMenu::update(sf::Vector2f mousePose)
{
}

void WinMenu::draw(sf::RenderWindow& window)
{
	window.draw(Background);
	window.draw(Text);
}
