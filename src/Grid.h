#pragma once
#include <SFML/Graphics.hpp>
#include "Levels.h"

#define HEIGHT 10
#define WIDTH 10

class Grid {
private:
    sf::Texture textures[6];              // Array to store the sprites
    sf::RenderWindow* window;             // Pointer to the main window
    std::vector<Level> levels;
    int currentLevel;
public:
    std::vector<std::vector<int>> grid;
public:
    Grid();
	void init(sf::RenderWindow& window);
	void loadLevels();
    void selecLevel(int levelNumber);
    void draw();
    std::pair<float, float> getPlayerSpawnPoint();
	std::vector<std::string> getLevelNames();
	Level getCurentLevel();
    int getCurrentLevelIndex();
};
