#include "Defeat.h"



Defeat::Defeat()
	:Text(font),
	ResetText(font),
	CloseText(font),
	backTexture("images/back.png"),
	backSprite(backTexture),
	restart("images/start.png"),
	restartSprite(restart)
{


	if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
		std::cerr << "Impossible de charger la police\n";

	backSprite.setTexture(backTexture);
	restartSprite.setTexture(restart);
	backSprite.setScale({ 0.6f, 0.6f });

	ResetText.setString("Press Spacebar to reset");
	ResetText.setCharacterSize(40);
	ResetText.setPosition({ 350,600 });
	ResetText.setFillColor(sf::Color::Blue);


	CloseText.setString("Press Escape to quit");
	CloseText.setCharacterSize(40);
	CloseText.setPosition({ 350,800 });
	CloseText.setFillColor(sf::Color::Green);

	backSprite.setScale({ 0.6f, 0.6f });


	create_Buttons();


}

void Defeat::clear_Buttons()
{
	for (auto* button : defeatButtons)
		delete button;
	defeatButtons.clear();
}

void Defeat::create_Buttons()
{
	clear_Buttons();
	defeatButtons.push_back(new Menu::Button("Restart", StartPos, StartSize, &restart));
}


void Defeat::display()
{
	create_Buttons();
}

void Defeat::update(const sf::Vector2f Mouse_Pose)
{
	for (auto* button : defeatButtons)
		button->update_Hover(Mouse_Pose);
}



void Defeat::HandleClick(const sf::Vector2f Mouse_Pose) {
	if (defeatButtons[0]->Clicked(Mouse_Pose))
	{
		currentState = GameState::Play;
	}

}




void Defeat::draw(sf::RenderWindow& window)
{


	window.draw(backSprite);
	for (auto* button : defeatButtons)
		button->draw(window);
	window.draw(Text);
	window.draw(ResetText);
	window.draw(CloseText);



}

