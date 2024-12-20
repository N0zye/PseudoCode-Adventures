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
	Grid* grid;
	sf::Texture playerTexture;	
	float x, y;
	bool hasKey;
public:
	Player();
	void init(sf::RenderWindow& window, Grid& grid);
	void executeCommand(Commands command);
	bool checkLevelCompletion();
	void draw();
};
