#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

#include "EventBus.h"
#include "Grid.h"
#include "Player.h"

class Game {
private:

	class CommandsParser {
	private:
		// Internal functions
		std::vector<std::string> tokenizeCode(std::string inputCode);
		std::string toUpper(std::string str);

	private:
		// Internal members
		std::queue<Commands> commands;

	public:
		// Constructor that takes an EventBus reference
		CommandsParser();

		// Public methods
		void parseCode(std::string code);
		Commands getNextCommand();
		bool empty();
	};


private:
	sf::RenderWindow& window;
	EventBus bus;
	Grid grid;
	Player player;
	CommandsParser parser;
private:
	void runCommand();
public:
	Game(sf::RenderWindow& window, EventBus& bus);
	void update();
	void setCode(std::string code);
	void loadLevel(int levelNumber);
	void draw();
};