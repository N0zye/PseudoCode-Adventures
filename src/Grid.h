#pragma once
#include <SFML/Graphics.hpp>

#define HEIGHT 10
#define WIDTH 10

struct Vector2 {
	float x, y;
};;

class Grid
{
private:
    sf::Texture textures[6];              // Array to store the sprites
    sf::RenderWindow* window;             // Pointer to the main window
public:
    int grid[WIDTH][HEIGHT] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 5, 1, 0, 0, 0}, // 5 is the exit
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 3, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 6, 0, 0}, // 6 is the player spawnpoint
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

public:
    Grid(sf::RenderWindow& window);
	Vector2 GetPlayerSpawnPoint();
    void Draw();
};
