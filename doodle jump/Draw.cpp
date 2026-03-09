#include "Draw.h"
#include "Setup.h"

Draw::Draw()
{
}

void Draw::draw(sf::RenderWindow& window)
{
	//dessiner le carre vert
	window.draw(Setup::m_playerShape);
}