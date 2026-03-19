#pragma once
#include "Menu.h"
#include "GameState.h"
#include <vector>

extern GameState currentState;

class Main_Menu : public Menu
{
private:

	sf::Texture background_texture;
	sf::Sprite background_sprite;

    sf::Texture Start;
	sf::Sprite Start_Sprite;

	sf::Texture Exit;
	sf::Sprite Exit_Sprite;

	sf::Vector2f StartPos{ 25.f, 350.f };
	sf::Vector2f StartSize{ 200.f, 120.f };

	sf::Vector2f ExitPos{ 25.f, 490.f };
	sf::Vector2f ExitSize{ 200.f, 120.f };

	sf::Texture Sound;
	sf::Sprite Sound_Sprite;

	sf::Vector2f SoundPos{ 25.f, 420.f };
	sf::Vector2f SoundSize{ 200.f, 120.f };


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