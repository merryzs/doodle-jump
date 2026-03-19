#include "Menu.h"

Menu::Button::Button(const std::string& lab,
    const sf::Vector2f& pos,
    const sf::Vector2f& size,
    sf::Texture* button_Texture)
    : lab(lab), 
    pos(pos), 
    size(size), 
    hover(false),
    button_texture(button_Texture),
	button_sprite(nullptr)
{
    button_shape.setSize(size);
    button_shape.setPosition(pos);
    button_shape.setFillColor(sf::Color::Blue);

    if (button_texture != nullptr)
    {
		button_sprite = new sf::Sprite(*button_texture);

		sf::Vector2u texSize = button_texture->getSize();
        button_sprite->setScale({ size.x / texSize.x, size.y / texSize.y  });
	
		button_sprite->setPosition(pos);
    }
}

Menu::Button::~Button()
{
        delete button_sprite;
		Button::button_sprite = nullptr;
}

void Menu::Button::update_Hover(const sf::Vector2f& Mouse_Pose)
{
    hover = button_shape.getGlobalBounds().contains(Mouse_Pose);
    button_shape.setFillColor(hover ? sf::Color::Green : sf::Color::Blue);
}

bool Menu::Button::Clicked(const sf::Vector2f& Mouse_Pose) const
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        return button_shape.getGlobalBounds().contains(Mouse_Pose);

    }
}

void Menu::Button::draw(sf::RenderWindow& window)
{
    if (button_sprite)
    {
        window.draw(*button_sprite);
    }
    else
       window.draw(button_shape);
}