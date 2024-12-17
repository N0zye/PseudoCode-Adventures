#include "Game.h"

Game::Game(sf::RenderWindow& window) : window(&window), grid(window), player(window, grid), parser() {}

void Game::runCommand() {
	return player.executeCommand(parser.getNextCommand());
}

void Game::update() {
	if (!parser.empty()) {
		runCommand();
	}
}

void Game::setCode(std::string code) {
	parser.parseCode(code);
}

void Game::draw() {
	grid.draw();
	player.draw();
}

void Game::loadLevel(int levelNumber) {
	grid.loadLevel(levelNumber);
}