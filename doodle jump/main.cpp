#include "lib.h"
#include "Draw.h"
#include "Player.h"
#include "Setup.h"

int main()
{


    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


	Draw draws;


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(draws);
        window.display();
    }
}