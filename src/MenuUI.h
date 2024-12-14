#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

void UIinit(sf::RenderWindow& window);
void ShowMainMenu();
std::string ShowCodeEditor(bool isButtonEnabled);
void ShowErrorMenu(std::string errorCommand);