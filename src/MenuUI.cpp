#include "MenuUI.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include <string>

void ShowInfoMenu();
void ShowLicenseMenu();
void ShowTutorialMenu();

sf::RenderWindow* window; // Pointer to the main window

std::string textBuffer(2048, '\0'); // Text buffer for the code editor
std::string CodeEditorReturn;

bool toogleInfoMenu = false;
bool toogleLicenseMenu = false;
bool toggleErrorMenu = false;
bool toggleTutorialMenu = false;

int currentLevel;

std::string errorCommand;

void UIinit(sf::RenderWindow& _window, int startingLevel) {
	window = &_window;
	currentLevel = startingLevel;
}

bool ShowMainMenu() {
	bool changesOccured = false;
	// Create a menu bar
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Pseudocode Adventures")) {
			if (ImGui::MenuItem("Esci")) {
				window->close();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Livelli")) { // Just 5 levels for now (and probably forever)
			if (ImGui::MenuItem("Livello 1", nullptr)) {
				currentLevel = 1;
				changesOccured = true;
			}
			if (ImGui::MenuItem("Livello 2", nullptr)) {
				currentLevel = 2;
				changesOccured = true;
			}
			if (ImGui::MenuItem("Livello 3", nullptr)) {
				currentLevel = 3;
				changesOccured = true;
			}
			if (ImGui::MenuItem("Livello 4", nullptr)) {
				currentLevel = 4;
				changesOccured = true;
			}
			if (ImGui::MenuItem("Livello 5", nullptr)) {
				currentLevel = 5;
				changesOccured = true;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Informazioni")) {
			if (ImGui::MenuItem("Crediti", nullptr)) {
				toogleInfoMenu = true;
			}
			if (ImGui::MenuItem("Licenza", nullptr)) {
				toogleLicenseMenu = true;
			}
			if (ImGui::MenuItem("GitHub Repository", nullptr)) {
				system("start https://github.com/N0zye/PseudoCode-Adventures.git");
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	// Show the secondary menus
	if (toogleInfoMenu) ShowInfoMenu();
	if (toogleLicenseMenu) ShowLicenseMenu();
	if (toggleErrorMenu) {
		ImGui::Begin("Errore", &toggleErrorMenu, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "Errore, comando: %s non riconosciuto.", errorCommand.c_str());
		ImGui::End();
	}
	if (toggleTutorialMenu) ShowTutorialMenu();

	return changesOccured; // no level change
}

std::string ShowCodeEditor(bool isButtonEnabled) {
	CodeEditorReturn = "";
	ImGui::Begin("#CodeEditor", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

	// Set window size and position
	const ImVec2 editorSize(window->getSize().x * 0.44921875f, window->getSize().y * 0.975);
	const ImVec2 editorPos(window->getSize().x * 0.55078125f, 30);
	ImGui::SetWindowSize(editorSize);
	ImGui::SetWindowPos(editorPos);

	if (ImGui::Button("Avvia", ImVec2(100, 30))) {
		if (isButtonEnabled) CodeEditorReturn = textBuffer.data();
	}
	ImGui::SameLine();

	if (ImGui::Button("Come giocare", ImVec2(200, 30))) {
		toggleTutorialMenu = true;
	}
	ImGui::SameLine();

	if (ImGui::Button("Resetta", ImVec2(150, 30))) {
		textBuffer = std::string(2048, '\0');
		// Find a way to reload the level.
		// it's going to require a level manager
	}

	ImGui::InputTextMultiline(
		"##TextInput",
		textBuffer.data(), textBuffer.size(),
		ImVec2(editorSize.x, editorSize.y - 60),
		ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_AllowTabInput
	);

	ImGui::End();
	if (!CodeEditorReturn.empty()) {
		return CodeEditorReturn;
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
	ImGui::SetNextWindowSize(ImVec2(1000, 436));

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

void ShowErrorMenu(std::string error) {
	toggleErrorMenu = true;
	errorCommand = error;
}

void ShowTutorialMenu() {
	ImGui::SetNextWindowSize(ImVec2(1660, 440));
	ImGui::Begin("Tutorial", &toggleTutorialMenu, ImGuiWindowFlags_NoCollapse);
	ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);

	ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.9f, 1.0f), "Benvenuto in PseudoCode Adventures, il gioco in cui devi scrivere il codice per far muovere il tuo personaggio (signor Oriani).");
	ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Ti occuperai di scrivere pseudocodice, una forma molto semplice di programmazione.");
	ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Il tuo obiettivo e' far raggiungere al signor Oriani la fine del livello, marcata dalla ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.9f, 0.3f, 0.3f, 1.0f), "X rossa");
	ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Per fare cio', dovrai scrivere una serie di comandi, per controllare il personaggio, tra i seguenti:");

	ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.4f, 1.0f), "SU");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "- muove verso l'alto di una casella");
	ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.4f, 1.0f), "GIU");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "- muove verso il basso di una casella");
	ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.4f, 1.0f), "DESTRA");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "- muove verso destra di una casella");
	ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.4f, 1.0f), "SINISTRA");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "- muove verso sinistra di una casella");
	ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.4f, 1.0f), "RACCOGLI");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "- fa raccogliere al signor Oriani la chiave, se una e' presente nella cella su cui si trova");
	ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.4f, 1.0f), "APRI");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "- fa aprire al signor Oriani la porta, se c'e' una porta chiusa in una delle caselle attorno a lui ed e' in possesso di una chiave");

	ImGui::TextColored(ImVec4(0.9f, 0.3f, 0.3f, 1.0f), "Attenzione:"); 
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.4f, 1.0f), "I comandi devono essere scritti esattamente come indicato, altrimenti non verranno riconosciuti e riceverai un messaggio di errore.");
	ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Non devi preoccuparti di lettere in maiuscolo e minuscolo, ci ho gia' pensato io ;)");
	ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Naturalmente non puoi passare dentro le pareti o porte chiuse, quindi i comandi che violano questa regola non vengono eseguiti.");

	ImGui::TextColored(ImVec4(0.4f, 0.9f, 0.4f, 1.0f), "Buona fortuna!");

	ImGui::PopTextWrapPos();
	ImGui::End();
}

int GetCurrentLevel() {
	return currentLevel;
}