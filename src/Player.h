#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"

enum Commands {
	SU,
	GIU,
	DESTRA,
	SINISTRA,
	RACCOGLI,
	APRI
};

class Player {
private:
	sf::RenderWindow* window;
	sf::Texture playerTexture;	
	Grid* grid;
	float x, y;
	bool hasKey;
public:
	Player(sf::RenderWindow& window, Grid& grid);
	void executeCommand(Commands command);
	void draw();
};
