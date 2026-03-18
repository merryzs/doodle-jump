#include "MainMenu.h"



Main_Menu::Main_Menu()
{
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
    MainMenuButtons.push_back(new Menu::Button("Play", { 300.f, 200.f }, { 200.f, 50.f }));
    MainMenuButtons.push_back(new Menu::Button("Exit", { 300.f, 300.f }, { 200.f, 50.f }));
}

void Main_Menu::display()
{
    // Logique d'affichage si nécessaire (déjà créés dans le constructeur)
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
    for (auto* button : MainMenuButtons)
        button->draw(window);
}