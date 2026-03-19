#include "Defeat.h"



Defeat::Defeat()
	:Text(font),
	ResetText(font),
	CloseText(font)
{
	if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
		std::cerr << "Impossible de charger la police\n";

	Background.setSize({ 1080 , 1080 });
	Background.setFillColor(sf::Color::Black);


	Text.setString("GAME OVER");
	Text.setCharacterSize(80);
	Text.setPosition({ 300,300 });
	Text.setFillColor(sf::Color::Red);

	ResetText.setString("Press Spacebar to reset");
	ResetText.setCharacterSize(40);
	ResetText.setPosition({ 350,600 });
	ResetText.setFillColor(sf::Color::Blue);


	CloseText.setString("Press Escape to quit");
	CloseText.setCharacterSize(40);
	CloseText.setPosition({ 350,800 });
	CloseText.setFillColor(sf::Color::Green);

}


void Defeat::display()
{

}

void Defeat::update(sf::Vector2<float> mousePos)
{
	//sert vrm a r
}




void Defeat::draw(sf::RenderWindow& window)
{
	window.draw(Background);
	window.draw(Text);
	window.draw(ResetText);
	window.draw(CloseText);



}

