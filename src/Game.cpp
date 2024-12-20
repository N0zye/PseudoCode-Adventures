#include "Game.h"

Game::CommandsParser::CommandsParser(){}

std::vector<std::string> Game::CommandsParser::tokenizeCode(std::string inputCode) {
	std::string processedCode = toUpper(inputCode);

	// Replace newlines with spaces
	std::replace(processedCode.begin(), processedCode.end(), '\n', ' ');

	std::vector<std::string> tokens;
	std::stringstream iss(processedCode);
	std::string token;

	while (iss >> token) {
		tokens.push_back(token);
	}
	return tokens;
}

std::string Game::CommandsParser::toUpper(std::string str) {
	std::string result = "";
	for (char& ch : str) {
		if (ch == 0) { // Null terminator check
			break;
		}
		else {
			result += std::toupper(ch);
		}
	}
	return result;
}

void Game::CommandsParser::parseCode(std::string code) {
	std::vector<std::string> tokenized = tokenizeCode(code);

	for (const std::string& command : tokenized) {
		if (command == "SU") {
			commands.push(Commands::SU);
		}
		else if (command == "GIU") {
			commands.push(Commands::GIU);
		}
		else if (command == "DESTRA") {
			commands.push(Commands::DESTRA);
		}
		else if (command == "SINISTRA") {
			commands.push(Commands::SINISTRA);
		}
		else if (command == "RACCOGLI") {
			commands.push(Commands::RACCOGLI);
		}
		else if (command == "APRI") {
			commands.push(Commands::APRI);
		}
		else if (command == " " || command == "\n") {
			continue; // Ignore spaces or newlines
		}
		else {
			// Handle invalid commands
			std::cerr << "Invalid command: " << command << std::endl;
			commands = std::queue<Commands>(); // empty the queue
			throw std::runtime_error("Errore: comando " + command + " non riconosciuto");
		}
	}
}

// Returns the next command from the queue
Commands Game::CommandsParser::getNextCommand() {
	Commands command = commands.front();
	commands.pop();
	return command;
}

// Returns true if the command queue is empty
bool Game::CommandsParser::empty() {
	return commands.empty();
}

Game::Game(sf::RenderWindow& window, EventBus& bus) : window(window), bus(bus), parser() {
	try {
		grid.init(window);
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		bus.publish(Event(EventType::Error, e.what()));
	}

	try {
		player.init(window, grid);
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		bus.publish(Event(EventType::Error, e.what()));
	}
	
	bus.publish(Event(EventType::GameReady, grid.getLevelNames()));

	// Subscribe to the run code button pressed event to set the code for the game
	bus.subscribe(EventType::RunCodeButtonPressed, [this](const Event& event) -> void {
		setCode(std::get<std::string>(event.getPayload()));
		});

	// Subscribe to the level selected event to load the level
	bus.subscribe(EventType::LevelSelected, [this](const Event& event) -> void {
		loadLevel(std::get<int>(event.getPayload()));
		});
}

void Game::runCommand() {
	player.executeCommand(parser.getNextCommand());
	if (player.checkLevelCompletion()) {
		bus.publish(Event(EventType::LevelCompleted, grid.getCurentLevel().name));
		// Clear the command queue
		while (!parser.empty()) {
			parser.getNextCommand();
		}	
		// load the next level if there is one, otherwise show a message
		if (grid.getCurentLevel().name != "Default level" && grid.getCurrentLevelIndex() < grid.getLevelNames().size() -1) {
			loadLevel(grid.getCurrentLevelIndex() + 1);
		}
	}
}

void Game::update() {
	if (!parser.empty()) {
		runCommand();
	}
}

void Game::setCode(std::string code) {
	try {
		parser.parseCode(code);
	}
	catch (std::runtime_error& e) {
		bus.publish(Event(EventType::Error, e.what()));
	}
}

void Game::draw() {
	grid.draw();
	player.draw();
}

void Game::loadLevel(int levelNumber) {
	if (levelNumber == -1) {
		levelNumber = grid.getCurrentLevelIndex();
	}
	grid.selecLevel(levelNumber);
	player.init(window, grid);
}