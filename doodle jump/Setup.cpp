#include "Setup.h"

Setup::Setup()
	: m_playerShape(),
	pose()
{
}

Setup::~Setup()
{

	//set dun carre vert
	m_playerShape.setSize({ 50.f,100.f });
	m_playerShape.setFillColor(sf::Color::Green);
	
	m_playerShape.setScale({ 1.f,1.f });

	//set de la pose

	pose = { 400.f,300.f };	

	m_playerShape.setPosition(pose);

}