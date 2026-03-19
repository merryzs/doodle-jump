#pragma once
#include "lib.h"
#include "GameState.h"



class Menu
{
public:
    struct Button
    {
        sf::RectangleShape button_shape;
        sf::Texture*       button_texture;
		sf::Sprite*		   button_sprite;
        std::string        lab;
        bool               hover;
        sf::Vector2f       pos;
        sf::Vector2f       size;

        Button(const std::string& lab,
            const sf::Vector2f& pos,
            const sf::Vector2f& size,
            sf::Texture* button_Texture = nullptr);

        virtual void update_Hover(const sf::Vector2f& Mouse_Pose);
        bool Clicked(const sf::Vector2f& Mouse_Pose) const;


        virtual void draw(sf::RenderWindow& window);
        virtual ~Button();


    };

    Menu() = default;
    virtual ~Menu() = default;

    virtual void display() = 0;
    virtual void update(const sf::Vector2f Mouse_Pose) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    bool clickedrestart;
    GameState handleInput(sf::RenderWindow& window, const sf::Event& event, GameState curState);
};