#include "Player.h"

Player::Player() {
    // ton code d'initialisation
}



void Player::display() {
 
	//set up carre
	hitbox.setSize({ 64.f, 64.f });
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2.f);

	//pose
	pose = { 375.f, 500.f };
	hitbox.setPosition(pose);


}

void Player::updates(float deltaTime) {

	float moveDistance = speed * deltaTime;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		
		
		pose.x -= moveDistance;
		
		
		std::cout << "Player moved left: " << pose.x << std::endl;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {


		pose.x += moveDistance;


		std::cout << "Player moved right: " << pose.x << std::endl;
	}


	hitbox.setPosition(pose);
}   

//void Player::handlecolisions() {
//	// Ton code de gestion des collisions
//}


void Player::draw(sf::RenderWindow& window) {

	window.draw(hitbox);

}