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

	sf::Texture backTexture;
	sf::Sprite backSprite;


	std::vector<Menu::Button*> defeatButtons;

	void create_Buttons();
	void clear_Buttons();

	sf::Texture restart;
	sf::Sprite restartSprite;

	sf::Vector2f StartPos{ 350.f ,  350.f };
	sf::Vector2f StartSize{ 400.f , 300.f };

	sf::Texture Exit;
	sf::Sprite ExitSprite;

public:


		Defeat();

		void display() override;
		void update(sf::Vector2<float> mouse_Pose) override;
		void HandleClick(const sf::Vector2f Mouse_Pose);

		void draw(sf::RenderWindow& window) override;



};

