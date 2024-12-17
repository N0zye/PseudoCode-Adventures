#include "Grid.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include "Levels.h"

#define LEVELSIZE sizeof(int) * HEIGHT * WIDTH

Grid::Grid(sf::RenderWindow& window) : window(&window) {

    // Loading textures
    sf::Texture grassTexture, wallTexture, keyTexture, closedDoorTexture, openDoorTexture, exitTexture;
    if (!grassTexture.loadFromFile("assets/textures/grass.png")) {
        std::cerr << "Error loading grass texture!" << std::endl;
    }
    if (!wallTexture.loadFromFile("assets/textures/wall.png")) {
        std::cerr << "Error loading wall texture!" << std::endl;
    }
	if (!keyTexture.loadFromFile("assets/textures/key.png")) {
		std::cerr << "Error loading key texture!" << std::endl;
	}
	if (!closedDoorTexture.loadFromFile("assets/textures/door.png", { 0,0, 100, 100 })) {
		std::cerr << "Error loading closed door texture!" << std::endl;
	}
	if (!openDoorTexture.loadFromFile("assets/textures/door.png", { 100,0, 100, 100 })) {
		std::cerr << "Error loading open door texture!" << std::endl;
	}
	if (!exitTexture.loadFromFile("assets/textures/exit.png")) {
		std::cerr << "Error loading exit texture!" << std::endl;
	}

	textures[0] = grassTexture;
	textures[1] = wallTexture;
	textures[2] = keyTexture;
	textures[3] = closedDoorTexture;
	textures[4] = openDoorTexture;
	textures[5] = exitTexture;

	// Load the first level
	loadLevel(1);
}

void Grid::loadLevel(int levelNumber) { //TODO: implement a better way to load levels (maybe from a file)
	switch (levelNumber) {
	case 1:
		std::memcpy(grid, level1, LEVELSIZE);
		break;
	default: // In case of unrecognized level
		std::memcpy(grid, level0, LEVELSIZE);
		break;
	}
}


void Grid::draw() {

	// Loading sprites
	sf::Sprite grass(textures[0]);
	sf::Sprite wall(textures[1]);
	sf::Sprite key(textures[2]);
	sf::Sprite closedDoor(textures[3]);
	sf::Sprite openDoor(textures[4]);
	sf::Sprite exit(textures[5]);

	// Scaling
	float scaling = (0.55078125f * window->getSize().x / WIDTH) / 100; // magic number, calculated to make precise squared proportions
	grass.setScale(scaling, scaling);
	wall.setScale(scaling, scaling);
	key.setScale(scaling, scaling);
	closedDoor.setScale(scaling, scaling);
	openDoor.setScale(scaling, scaling);
	exit.setScale(scaling, scaling);

	// Drawing
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
			switch (grid[i][j]) { // Use i for rows and j for columns or vice versa idk at this point. matrices are just confusing af
            case 0:
                grass.setPosition(j * 100 * scaling, i * 100 * scaling + 30);
                window->draw(grass);
                break;
            case 1:
                wall.setPosition(j * 100 * scaling, i * 100 * scaling + 30);
                window->draw(wall);
                break;
            case 2:
                key.setPosition(j * 100 * scaling, i * 100 * scaling + 30);
                window->draw(key);
                break;
            case 3:
                closedDoor.setPosition(j * 100 * scaling, i * 100 * scaling + 30);
                window->draw(closedDoor);
                break;
            case 4:
                openDoor.setPosition(j * 100 * scaling, i * 100 * scaling + 30);
                window->draw(openDoor);
                break;
            case 5: 
                exit.setPosition(j * 100 * scaling, i * 100 * scaling + 30);
                window->draw(exit);
                break;
			case 6: // handle the player starting position as grass then draw the player on top
				grass.setPosition(j * 100 * scaling, i * 100 * scaling + 30);
				window->draw(grass);
				break;
            }   
        }
    }
}

std::pair<float, float> Grid::getPlayerSpawnPoint() {
	std::pair<float, float> result(0,0);
	float playerScaling = (0.55078125f * window->getSize().x / WIDTH) / 200; // Cuz player texture is 200x200
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (grid[i][j] == 6) {
				result.first = j * 200 * playerScaling;
				result.second = i * 200 * playerScaling + 30;
				return result;
			}
		}
	}
	return result;
}