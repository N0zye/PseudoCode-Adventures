#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include <SFML\Graphics.hpp>
#include "MenuUI.h"
#include "Player.h"

#include <iostream>

int main() {
	// Window setup
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pseudocode Adventures", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	// ImGui-SFML initialization
	ImGui::SFML::Init(window);
	UIinit(window); // to initialize the UI functions

	// Load fonts
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear(); // Clear fonts if you loaded some before (even if it's the default one)
	io.Fonts->AddFontFromFileTTF("assets/fonts/Inconsolata-Regular.ttf", 24.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
	io.Fonts->Build();
	ImGui::SFML::UpdateFontTexture(); // If this is the solution I'll kill myself (it is) 

	Player player(window);

	sf::Clock deltaTime;
	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
				int key = event.key.code;
				if (key == -1) { // The only one I found that gives problems is CAPSLOCK
					continue;
				}
			}
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			ImGui::SFML::ProcessEvent(event);
		}
		ImGui::SFML::Update(window, deltaTime.restart());


		// ImGui debug windows
#ifdef _DEBUG
		ImGui::ShowMetricsWindow();
		//ImGui::ShowDemoWindow();
		//ImGui::ShowFontSelector("##FontSelector");
		//ImGui::ShowStyleSelector("##StyleSelector");
#endif // _DEBUG




// ImGui code
		ShowMainMenu();
		std::string code = ShowCodeEditor();
		if (code != "") {
			// Do something with the code
		}
		window.clear();
		ImGui::SFML::Render(window);
		player.Draw();
		window.display();

	}

	// Cleanup
	ImGui::SFML::Shutdown();
	return 0;
}