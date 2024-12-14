#include "Player.h"
#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

Player::Player(sf::RenderWindow& window, Grid& grid) 
	: window(&window), hasKey(false), grid(grid) {
	if (!playerTexture.loadFromFile("assets/textures/player.png")) {
		std::cerr << "Error loading player texture!" << std::endl;
	}
	x = grid.GetPlayerSpawnPoint().x;
	y = grid.GetPlayerSpawnPoint().y;
}

void Player::Draw() {
	sf::Sprite player(playerTexture);
	float scaling = (0.55078125f * window->getSize().x / WIDTH) / 200;
	// magic number, calculated to make precise squared proportions
	player.setScale(scaling, scaling);
	player.setPosition(x, y);
	window->draw(player);
}

void Player::Update(Commands command) {
	float gridcellSize = (0.55078125f * window->getSize().x / WIDTH);
	int scaledX = x / gridcellSize;
	int scaledY = (y - 30) / gridcellSize;
	int upGridCellType = grid.grid[scaledX][scaledY - 1];
	int downGridCellType = grid.grid[scaledX][scaledY + 1];
	int leftGridCellType = grid.grid[scaledX - 1][scaledY];
	int rightGridCellType = grid.grid[scaledX + 1][scaledY];
	switch (command)
	{
	case SU:
		if (upGridCellType != 1 && upGridCellType != 3) {
			if (y >= gridcellSize) y -= gridcellSize;
		}
		break;
	case GIU:
		if (downGridCellType != 1 && downGridCellType != 3) {
			if (y <= 0.55078125f * window->getSize().y - 2 * gridcellSize) y += gridcellSize;
		}
		break;
	case DESTRA:
		if (rightGridCellType != 1 && rightGridCellType != 3) {
			if (x <= 0.55078125f * window->getSize().x - 2 * gridcellSize) x += gridcellSize;
		}
		break;
	case SINISTRA:
		if(leftGridCellType != 1 && leftGridCellType != 3) {
			if (x >= gridcellSize) x -= gridcellSize; 
		}
		break;
	case RACCOGLI:
		if (grid.grid[scaledX][scaledY] == 2) {
			grid.grid[scaledX][scaledY] = 0;
			hasKey = true;
		}
		break;
	case APRI:
		std::cout << hasKey << std::endl;
		if (leftGridCellType == 3 && hasKey) {
			grid.grid[scaledX - 1][scaledY] = 4;
		}
		else if (rightGridCellType == 3 && hasKey) {
			grid.grid[scaledX + 1][scaledY] = 4;
		}
		else if (upGridCellType == 3 && hasKey) {
			grid.grid[scaledX][scaledY - 1] = 4;
		}
		else if (downGridCellType == 3 && hasKey) {
			grid.grid[scaledX][scaledY + 1] = 4;
		}
		break;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
