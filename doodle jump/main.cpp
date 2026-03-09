#include "lib.h"
#include "Player.h"

int main()
{


    sf::RenderWindow window(sf::VideoMode({ 750, 1050 }), "SFML works!");
	window.setFramerateLimit(60);  

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;

	
	Player player;




    player.display();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

		float deltaTime = clock.restart().asSeconds();
		player.updates(deltaTime);

        //cleae
        window.clear();


       //update



        //draw
		player.draw(window);


		//display
        window.display();
    }
}