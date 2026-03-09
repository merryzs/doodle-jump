#include "Setup.h"

Setup::Setup()
	: m_playerShape()
{
}

Setup::~Setup()
{
	m_playerShape.setSize({ 50.f,100.f });
	m_playerShape.setFillColor(sf::Color::Green);
	m_playerShape.setPosition({ 400.f,300.f });
	m_playerShape.setScale({ 1.f,1.f });


}