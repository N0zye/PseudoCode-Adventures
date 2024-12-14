#pragma once

#include "SFML/Graphics.hpp"
#include "Grid.h"
#include <queue>

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
	float x, y;
	sf::Texture playerTexture;
	bool hasKey;
	Grid& grid;
public:
	Player(sf::RenderWindow& window, Grid& grid);
	void Draw();
	void Update(Commands command);
};
