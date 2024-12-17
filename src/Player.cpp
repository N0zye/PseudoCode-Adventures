#include "Player.h"
#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

Player::Player(sf::RenderWindow& window, Grid& grid) {
	this->window = &window;
	this->grid = &grid;

	x = grid.getPlayerSpawnPoint().first;
	y = grid.getPlayerSpawnPoint().second;

	hasKey = false;
	
	if (!playerTexture.loadFromFile("assets/textures/player.png")) {
		std::cerr << "Error loading player texture!" << std::endl;
	}
}

void Player::draw() {
	sf::Sprite player(playerTexture);
	float scaling = (0.55078125f * window->getSize().x / WIDTH) / 200;
	// magic number, calculated to make precise squared proportions
	player.setScale(scaling, scaling);
	player.setPosition(x, y);
	window->draw(player);
}

void Player::executeCommand(Commands command) {
	// Scaling factor to get the grid cell size
	float gridcellSize = (0.55078125f * window->getSize().x / WIDTH);

	// Scaling the player's position to the grid
	int scaledX = x / gridcellSize;
	int scaledY = (y - 30) / gridcellSize;

	// Getting the type of the player's neighbouring cells
	int upGridCellType = grid->grid[scaledY - 1][scaledX];
	int downGridCellType = grid->grid[scaledY + 1][scaledX];
	int leftGridCellType = grid->grid[scaledY][scaledX - 1];
	int rightGridCellType = grid->grid[scaledY][scaledX + 1];

	switch (command)
	{
	case SU:
		if (upGridCellType != 1 && upGridCellType != 3) {
			if (y >= gridcellSize) y -= gridcellSize;
		}
		break;
	case GIU:
		if (downGridCellType != 1 && downGridCellType != 3) {
			if (y <= window->getSize().y - 2*gridcellSize) y += gridcellSize;
		}
		break;
	case DESTRA:
		if (rightGridCellType != 1 && rightGridCellType != 3) {
			if (x <= 0.55078125f * window->getSize().x - gridcellSize - 30) x += gridcellSize;
		}
		break;
	case SINISTRA:
		if(leftGridCellType != 1 && leftGridCellType != 3) {
			if (x >= gridcellSize) x -= gridcellSize; 
		}
		break;
	case RACCOGLI:
		if (grid->grid[scaledY][scaledX] == 2) { // If the player is on a key
			grid->grid[scaledY][scaledX] = 0;    // Remove the key from the grid
			hasKey = true;						 // And give it to the player
		}
		break;
	case APRI:
		if (hasKey) {                            // Player needs to have a key to open the door

			// Check the neighbouring cells to find the door and open it
			if (leftGridCellType == 3) {
				grid->grid[scaledY][scaledX - 1] = 4;
				hasKey = false;
			}
			else if (rightGridCellType == 3) {
				grid->grid[scaledY][scaledX + 1] = 4;
				hasKey = false;
			}
			else if (upGridCellType == 3) {
				grid->grid[scaledY - 1][scaledX] = 4;
				hasKey = false;
			}
			else if (downGridCellType == 3) {
				grid->grid[scaledY + 1][scaledX] = 4;
				hasKey = false;
			}
		}
		break;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
