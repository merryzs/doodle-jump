#include "Player.h"

Player::Player()
	:sprite(texture)
{
	
}



void Player::display() {


	if (!texture.loadFromFile("assets/miku.png")) {
		std::cerr << "pas lad!" << std::endl;
	}





	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 64, 64 }));
	sprite.setScale({ 1.f, 1.f });
	sprite.setPosition(pose);





	
	hitbox.setSize({ 64.f, 64.f });
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2.f);

	
	pose = { 375.f, 500.f };
	hitbox.setPosition(pose);


}

void Player::updates(float deltaTime) {

	float moveDistance = speed * deltaTime;




	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {


		pose.x -= moveDistance;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {

		pose.x += moveDistance;
	}

	if (isGrounded == true) {
		velocityY = jumpStrength;
		isGrounded = false;

	}




	
	velocityY += gravity * deltaTime;
	pose.y += velocityY * deltaTime;

	if (isGrounded && velocityY > 0)
		velocityY = 0;

	

	hitbox.setPosition(pose);
	sprite.setPosition(pose);
}
void Player::warp()
{

	float Border_Left = -64.f;
	float Border_Right = 1080.f;

	if (pose.x <= Border_Left)
	{
		pose.x = 1070;
		hitbox.setPosition(pose);

	}

	if (pose.x >= Border_Right)
	{
		pose.x = -50;
		hitbox.setPosition(pose);
	}



}

void Player::reset()
{
	pose = { 375.f, 500.f };
	velocityY = 0;
	isGrounded = false;

	sprite.setPosition(pose);
	hitbox.setPosition(pose);
}

void Player::draw(sf::RenderWindow& window)
{

	window.draw(hitbox);
	window.draw(sprite);

}