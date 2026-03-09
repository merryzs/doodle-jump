#include "lib.h"
#include "Draw.h"
#include "Player.h"
#include "Setup.h"

int main()
{


    sf::RenderWindow window(sf::VideoMode({ 750, 1050 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


	Draw draws;
	Setup setup;
	

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //cleae
        window.clear();

        setup.setups();
        //draw
		setup.draw(window);


		//display
        window.display();
    }
}