#include "Player.h"

Player::Player() 
	:sprite(texture)
{
    // ton code d'initialisation
}



void Player::display() {
 

	if(!texture.loadFromFile("assets/miku.png")) {
		std::cerr << "pas lad!" << std::endl;
	}
	




	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 64, 64 }));
	sprite.setScale({ 1.f, 1.f });
	sprite.setPosition(pose);





	//set up carre
	hitbox.setSize({ 64.f, 64.f });
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2.f);

	//pose
	pose = { 375.f, 700.f };
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isGrounded) {
		velocityY = jumpStrength;
		isGrounded = false;
	}

	//gravity
	velocityY += gravity * deltaTime;
	pose.y += velocityY * deltaTime;

	//coli sol
	if (pose.y >= groundLevel) {
		pose.y = groundLevel;
		velocityY = 0.f;
		isGrounded = true;
	}

	hitbox.setPosition(pose);
	sprite.setPosition(pose);
}   

//void Player::handlecolisions() {
//	// Ton code de gestion des collisions
//}


void Player::draw(sf::RenderWindow& window) {

	window.draw(hitbox);
	window.draw(sprite);

}