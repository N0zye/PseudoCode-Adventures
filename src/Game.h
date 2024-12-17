#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include "Grid.h"
#include "Player.h"

class Game {
private:


	class CommandsParser {
	private:
		// Internal functions
		std::vector<std::string> tokenizeCode(std::string inputCode) {
			std::string processedCode = toUpper(inputCode);

			// Replace newlines with spaces
			std::replace(processedCode.begin(), processedCode.end(), '\n', ' ');

			std::vector<std::string> tokens;
			std::istringstream iss(processedCode);
			std::string token;

			while (iss >> token) {
				tokens.push_back(token);
			}
			return tokens;
		}

		std::string toUpper(std::string str) {
			std::string result = str;
			for (char& ch : result) {
				ch = std::toupper(ch);
			}
			return result;
		}
	private:
		// Internal members
		std::queue<Commands> commands;
	public:
		CommandsParser() {}

		void parseCode(std::string code) {
			std::vector<std::string> tokenized = tokenizeCode(code);

			for (const std::string& command : tokenized) {
				if (command == "SU") {
					commands.push(SU);
				}
				else if (command == "GIU") {
					commands.push(GIU);
				}
				else if (command == "DESTRA") {
					commands.push(DESTRA);
				}
				else if (command == "SINISTRA") {
					commands.push(SINISTRA);
				}
				else if (command == "RACCOGLI") {
					commands.push(RACCOGLI);
				}
				else if (command == "APRI") {
					commands.push(APRI);
				}
				else if (command == " " || command == "\n") {
					continue; // Ignore spaces
				}
				else {
					// Handle invalid commands
					std::cerr << "Invalid command: " << command << std::endl;
					throw std::runtime_error(command);
				}
			}
		}

		Commands getNextCommand() {
			Commands command = commands.front();
			commands.pop();
			return command;
		}

		bool empty() {
			return commands.empty();
		}
	};


private:
	sf::RenderWindow* window;
	Grid grid;
	Player player;
	CommandsParser parser;
private:
	void runCommand();
public:
	Game(sf::RenderWindow& window);
	void update();
	void setCode(std::string code);
	void loadLevel(int levelNumber);
	void draw();
};