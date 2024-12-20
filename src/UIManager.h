#pragma once

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#include "EventBus.h"

class UIManager {
private:
	sf::RenderWindow& window;
	EventBus& bus;
	std::string textBuffer;

	// State variables
	bool showCreditsMenu;
	bool showLicenseMenu;
	bool showPopUpMenu;
	bool showTutorialMenu;

	std::string popUpMessage;

	std::vector<std::string> levelNames;

	ImVec4 messageColor;

public:
	UIManager(sf::RenderWindow& window, EventBus& bus);

	void displayMainMenuBar();
	void displayCodeEditor();
	void triggerPopUp(std::string message, ImVec4 color);
private:
	// Refactored to be popups instead of windows
	void displayCreditsMenu();
	void displayLicenseMenu();
	void displayPopUp();
	void displayTutorialMenu();
};