#include "Menu.h"

Menu::Button::Button(const std::string& lab,
    const sf::Vector2f& pos,
    const sf::Vector2f& size)
    : lab(lab), pos(pos), size(size), hover(false)
{
    button_shape.setSize(size);
    button_shape.setPosition(pos);
    button_shape.setFillColor(sf::Color::Blue);
}

void Menu::Button::update_Hover(const sf::Vector2f& Mouse_Pose)
{
    hover = button_shape.getGlobalBounds().contains(Mouse_Pose);
    button_shape.setFillColor(hover ? sf::Color::Green : sf::Color::Blue);
}

bool Menu::Button::Clicked(const sf::Vector2f& Mouse_Pose) const
{
    return button_shape.getGlobalBounds().contains(Mouse_Pose);
}

void Menu::Button::draw(sf::RenderWindow& window)
{
    window.draw(button_shape);
}