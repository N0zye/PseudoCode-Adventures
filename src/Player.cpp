#include "Player.h"

Player::Player(sf::RenderWindow& window) {
	this->window = &window;
}

void Player::Draw() {
	sf::RectangleShape player(sf::Vector2f(50, 50));
	player.setFillColor(sf::Color::Green);
	player.setPosition(100, 100);
	window->draw(player);
}