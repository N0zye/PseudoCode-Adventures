#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

void UIinit(sf::RenderWindow& window, int startingLevel);
bool ShowMainMenu();
std::string ShowCodeEditor(bool isButtonEnabled);
void ShowErrorMenu(std::string errorCommand);
int GetCurrentLevel();