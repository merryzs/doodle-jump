#include "Defeat.h"



Defeat::Defeat()
	:Text(font),
	ResetText(font),
	CloseText(font),
	backTexture("images/back.png"),
	backSprite(backTexture),
	restart("images/start.png"),
	restartSprite(restart),
	Exit("images/leave.png"),
	ExitSprite(Exit)

{


	backSprite.setTexture(backTexture);
	restartSprite.setTexture(restart);
	backSprite.setScale({ 0.6f, 0.6f });

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
	defeatButtons.push_back(new Menu::Button("Menu", { StartPos.x, StartPos.y + 150.f }, StartSize, &restart));
	defeatButtons.push_back(new Menu::Button("Exit", { StartPos.x, StartPos.y + 300.f }, StartSize, &Exit));
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
		clickedrestart = true;
		currentState = GameState::Play;
	}
	else if (defeatButtons[1]->Clicked(Mouse_Pose))
	{
		currentState = GameState::Main_Menu;
	}
	else if (defeatButtons[2]->Clicked(Mouse_Pose))
	{
		exit(0);	
	}

}




void Defeat::draw(sf::RenderWindow& window)
{


	window.draw(backSprite);
	for (auto* button : defeatButtons)
		button->draw(window);




}

