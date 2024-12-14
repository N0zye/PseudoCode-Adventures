#include "Game.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <sstream>


std::vector<std::string> TokenizeCode(std::string inputCode); // Internal function declaration

Game::Game(sf::RenderWindow& window) : window(&window), grid(window), player(window, grid) {}

void Game::runCommand(Commands command) {
	return player.Update(command);
}

void Game::Draw() {
	grid.Draw();
	player.Draw();
}



std::queue<Commands> ParseCode(std::string code) {
	std::vector<std::string> tokenized = TokenizeCode(code);
	std::queue<Commands> commands;

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
	return commands;
}

std::string ToUpper(std::string str) {
	std::string result = str;
	for (char& ch : result) {
		ch = std::toupper(ch);
	}
	return result;
}

// Tokenize the input string into a vector of commands
std::vector<std::string> TokenizeCode(std::string inputCode) {
	std::string processedCode = inputCode;

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
