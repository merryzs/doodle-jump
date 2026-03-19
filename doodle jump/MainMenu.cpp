#include "MainMenu.h"



Main_Menu::Main_Menu()
    :background_texture("images/backmenu.png"),
    background_sprite(background_texture),
    Start("images/start.png"),
    Start_Sprite(Start),
    Exit("images/leave.png"),
    Exit_Sprite(Exit),
	Sound("images/Sound.png"),
	Sound_Sprite(Sound)


{

	background_sprite.setScale({0.6, 0.6});

	Start_Sprite.setScale({ 2.f, 2.f });
	Exit_Sprite.setScale({ 2.f, 2.f });


    create_Buttons();
}

Main_Menu::~Main_Menu()
{
    clear_Buttons();
}

void Main_Menu::clear_Buttons()
{
    for (auto* button : MainMenuButtons)
        delete button;
    MainMenuButtons.clear();
}

void Main_Menu::create_Buttons()
{
    clear_Buttons();
    MainMenuButtons.push_back(new Menu::Button("Play", StartPos, StartSize, &Start));
    MainMenuButtons.push_back(new Menu::Button("Exit", ExitPos, ExitSize, &Exit));
	MainMenuButtons.push_back(new Menu::Button("Sound", SoundPos, SoundSize, &Sound));
}

void Main_Menu::display()
{
    create_Buttons();
}

void Main_Menu::update(const sf::Vector2f Mouse_Pose)
{
    for (auto* button : MainMenuButtons)
        button->update_Hover(Mouse_Pose);



}
void Main_Menu::HandleClick(const sf::Vector2f Mouse_Pose)
{

    if (MainMenuButtons[0]->Clicked(Mouse_Pose))
    {
        currentState = GameState::Play;
    }

    else if (MainMenuButtons[1]->Clicked(Mouse_Pose))
    {
        exit(0);
    }
}

void Main_Menu::draw(sf::RenderWindow& window)
{
	window.draw(background_sprite);
    for (auto* button : MainMenuButtons)
        button->draw(window);
}