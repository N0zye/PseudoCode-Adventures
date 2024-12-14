#pragma once

#include "SFML/Graphics.hpp"
#include "Grid.h"
#include "Player.h"

class Game {
private:
	sf::RenderWindow* window;
	Grid grid;
	Player player;
public:
	Game(sf::RenderWindow& window);
	void runCommand(Commands command);
	void Draw();
};

std::queue<Commands> ParseCode(std::string code);