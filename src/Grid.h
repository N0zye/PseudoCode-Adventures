#pragma once
#include <SFML/Graphics.hpp>
#include "Levels.h"

class Grid
{
private:
    sf::Texture textures[6];              // Array to store the sprites
    sf::RenderWindow* window;             // Pointer to the main window
public:
    int grid[HEIGHT][WIDTH];

public:
    Grid(sf::RenderWindow& window);
    void loadLevel(int levelNumber);
    void draw();
    std::pair<float, float> getPlayerSpawnPoint();
};
