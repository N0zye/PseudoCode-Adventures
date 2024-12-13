#pragma once

#include "SFML/Graphics.hpp"

class Player {
private:
	sf::RenderWindow* window;
	int x, y;
public:
	Player(sf::RenderWindow& window);
	void Draw();
};

