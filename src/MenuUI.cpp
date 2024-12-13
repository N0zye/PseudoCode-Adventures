#include "MenuUI.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include <string>

void ShowInfoMenu();
void ShowLicenseMenu();

sf::RenderWindow* window; // Pointer to the main window

std::string textBuffer(2048, '\0'); // Text buffer for the code editor
std::string CodeEditorReturn;

bool toogleInfoMenu = false;
bool toogleLicenseMenu = false;


void UIinit(sf::RenderWindow& _window) {
	window = &_window;
}

void ShowMainMenu() {
	// Create a menu bar
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Pseudocode Adventures")) {
			if (ImGui::MenuItem("Exit")) {
				window->close();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Options")) {
			ImGui::MenuItem("non ho fatto in tempo", nullptr);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("About")) {
			if (ImGui::MenuItem("Credits", nullptr)) {
				toogleInfoMenu = true;
			}
			if (ImGui::MenuItem("License", nullptr)) {
				toogleLicenseMenu = true;
			}
			if (ImGui::MenuItem("GitHub Repository", nullptr)) {
				system("start https://github.com/N0zye/PseudoCode-Adventures.git");
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	// Show the info menu
	if (toogleInfoMenu) ShowInfoMenu();
	if (toogleLicenseMenu) ShowLicenseMenu();
}

std::string ShowCodeEditor() {
	// Code editor window
	CodeEditorReturn = "";
	ImGui::Begin("#CodeEditor", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

	// Set window size and position based on the parent window dimensions
	const ImVec2 editorSize(window->getSize().x * 0.40f, window->getSize().y * 0.975);
	const ImVec2 editorPos(window->getSize().x * 0.60f, 30);
	ImGui::SetWindowSize(editorSize);
	ImGui::SetWindowPos(editorPos);

	if (ImGui::Button("Avvia", ImVec2(100, 30))) {
		CodeEditorReturn = textBuffer;
	}
	ImGui::InputTextMultiline("##TextInput", textBuffer.data(), textBuffer.size(),
		ImVec2(editorSize.x, editorSize.y - 60), // To fix for the button
		ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_AllowTabInput);

	ImGui::End();
	if (CodeEditorReturn != "") {
		CodeEditorReturn = "";
		return textBuffer;
	}
	else {
		return "";
	}
}

void ShowInfoMenu() {
	ImGui::Begin("Pseudocode Adventures", &toogleInfoMenu, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Realizzato da Michele Berni 4D(sa) Corso Scienze Applicate - A.S. 2024/2025");
	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Per gli open day del liceo scientifico A. Oriani di Ravenna");
	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Il progetto e' open source e disponibile su GitHub");
	ImGui::End();
}

void ShowLicenseMenu() {
	ImGui::SetNextWindowSize(ImVec2(1000, 390), ImGuiCond_Once);

	ImGui::Begin("License", &toogleLicenseMenu, ImGuiWindowFlags_NoCollapse);

	// Enable text wrapping
	ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);

	// Display the CC BY-NC-SA license text with wrapping
	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "CC BY-NC-SA License");
	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
		"This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. You are free to:");

	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
		"- Share: copy and redistribute the material in any medium or format\n"
		"- Adapt: remix, transform, and build upon the material\n"
		"Under the following terms:");

	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
		"- Attribution: You must give appropriate credit, provide a link to the license, and indicate if changes were made.\n"
		"- NonCommercial: You may not use the material for commercial purposes.\n"
		"- ShareAlike: If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.");

	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
		"No additional restrictions: You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.");

	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
		"For more details, see the full license text at:");

	if (ImGui::Button("https://creativecommons.org/licenses/by-nc-sa/4.0/", ImVec2(1000, 30))) {
		// Open the license link in the default web browser
		system("start https://creativecommons.org/licenses/by-nc-sa/4.0/");
	}

	// Restore default text wrapping
	ImGui::PopTextWrapPos();

	ImGui::End();
}