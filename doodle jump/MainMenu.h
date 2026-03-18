#pragma once
#include "Menu.h"
#include "GameState.h"
#include <vector>

extern GameState currentState;

class Main_Menu : public Menu
{
private:


    std::vector<Menu::Button*> MainMenuButtons;

    void create_Buttons();
    void clear_Buttons();

public:
    Main_Menu();
    ~Main_Menu() override;

    void display()                              override;
    void update(const sf::Vector2f Mouse_Pose)  override;
    void HandleClick(const sf::Vector2f Mouse_Pose);
    void draw(sf::RenderWindow& window)          override;
};