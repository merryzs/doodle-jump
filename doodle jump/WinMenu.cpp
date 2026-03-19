#include "WinMenu.h"

WinMenu::WinMenu()
	:Text(font),
	ResetText(font),
	CloseText(font),
	winTexture("images/back.png"),
	winSprite(winTexture),
	restart("images/start.png"),
	restartSprite(restart),
	Exit("images/leave.png"),
	ExitSprite(Exit)

{


	winSprite.setTexture(winTexture);
	restartSprite.setTexture(restart);
	winSprite.setScale({ 0.6f, 0.6f });

	winSprite.setScale({ 0.6f, 0.6f });


	create_Buttons();


}

void WinMenu::clear_Buttons()
{
	for (auto* button : winButtons)
		delete button;
	winButtons.clear();
}

void WinMenu::create_Buttons()
{
	clear_Buttons();
	winButtons.push_back(new Menu::Button("Restart", StartPos, StartSize, &restart));
	winButtons.push_back(new Menu::Button("Menu", { StartPos.x, StartPos.y + 150.f }, StartSize, &restart));
	winButtons.push_back(new Menu::Button("Exit", { StartPos.x, StartPos.y + 300.f }, StartSize, &Exit));
}


void WinMenu::display()
{
	create_Buttons();
}

void WinMenu::update(const sf::Vector2f Mouse_Pose)
{
	for (auto* button : winButtons)
		button->update_Hover(Mouse_Pose);
}



void WinMenu::HandleClick(const sf::Vector2f Mouse_Pose) {
	if (winButtons[0]->Clicked(Mouse_Pose))
	{
		clickedrestart = true;
		currentState = GameState::Play;
	}
	else if (winButtons[1]->Clicked(Mouse_Pose))
	{
		currentState = GameState::Main_Menu;
	}
	else if (winButtons[2]->Clicked(Mouse_Pose))
	{
		exit(0);
	}

}




void WinMenu::draw(sf::RenderWindow& window)
{


	window.draw(winSprite);
	for (auto* button : winButtons)
		button->draw(window);




}
