#include "UIManager.h"

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

UIManager::UIManager(sf::RenderWindow& window, EventBus& bus) 
	: window(window), bus(bus), textBuffer(2048, '\0'), showCreditsMenu(false), showLicenseMenu(false), showPopUpMenu(false), showTutorialMenu(false), popUpMessage("") {
	bus.subscribe(EventType::Error, [&](const Event& event) {
		triggerPopUp(std::get<std::string>(event.getPayload()), ImVec4(0.9f, 0.3f, 0.3f, 1.0f));
		});
	bus.subscribe(EventType::GameReady, [&](const Event& event) {
		levelNames = std::get<std::vector<std::string>>(event.getPayload());
		});
	bus.subscribe(EventType::LevelCompleted, [&](const Event& event) {
		triggerPopUp("Congratulazioni, hai completato il livello: " + std::get<std::string>(event.getPayload()), ImVec4(0.4f, 0.9f, 0.4f, 1.0f)); // TODO: Add a color to the message
		});
}

void UIManager::displayMainMenuBar() {
	if (ImGui::BeginMainMenuBar()) {

		// Pseudocode Adventures menu
		if (ImGui::BeginMenu("Pseudocode Adventures")) {
			if (ImGui::MenuItem("Esci")) {
				window.close();
			}
			ImGui::EndMenu();
		}

		// Level selection menu
		if (ImGui::BeginMenu("Livelli")) {
			for (int i = 0; i < levelNames.size(); i++) {
				if (ImGui::MenuItem(levelNames[i].c_str(), nullptr)) {
					bus.publish(Event(EventType::LevelSelected, i));
				}
			}
			ImGui::EndMenu();
		}

		// Information menu
		if (ImGui::BeginMenu("Informazioni")) {
			// This should be popups insted of windows
			if (ImGui::MenuItem("Crediti", nullptr)) {
				showCreditsMenu = true;
			}
			if (ImGui::MenuItem("Licenza", nullptr)) {
				showLicenseMenu = true;
			}
			if (ImGui::MenuItem("GitHub Repository", nullptr)) {
				system("start https://github.com/N0zye/PseudoCode-Adventures.git");
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	// Show the secondary menus
	if (showCreditsMenu) displayCreditsMenu();
	if (showLicenseMenu) displayLicenseMenu();
	if (showPopUpMenu) displayPopUp();
	if (showTutorialMenu) displayTutorialMenu();
}

void UIManager::displayCodeEditor() {

	const ImVec2 editorSize(window.getSize().x * 0.44921875f, window.getSize().y * 0.975);
	ImGui::SetNextWindowSize(editorSize);
	ImGui::SetNextWindowPos(ImVec2(window.getSize().x * 0.55078125f, 30));
	ImGui::Begin("#CodeEditor", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);

	if (ImGui::Button("Avvia", ImVec2(100, 30))) {
		bus.publish(Event(EventType::RunCodeButtonPressed, textBuffer)); // Note: EvBus stuff is in development
	}

	ImGui::SameLine();
	if (ImGui::Button("Come giocare", ImVec2(200, 30))) {
		showTutorialMenu = true;
	}

	ImGui::SameLine();
	if (ImGui::Button("Resetta", ImVec2(150, 30))) {
		textBuffer = std::string(2048, '\0');
		bus.publish(Event(EventType::LevelSelected, -1)); // Reload the current level
	}

	ImGui::InputTextMultiline(
		"##TextInput",
		textBuffer.data(), textBuffer.size(),
		ImVec2(editorSize.x, editorSize.y - 60),
		ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_AllowTabInput
	);

	ImGui::End();
}

void UIManager::triggerPopUp(std::string message, ImVec4 color) {
	popUpMessage = message;
	showPopUpMenu = true;
	messageColor = color;
}


// Private methods
void UIManager::displayCreditsMenu() {
	ImGui::OpenPopup("Crediti");
	if (ImGui::BeginPopupModal("Crediti", &showCreditsMenu, ImGuiWindowFlags_AlwaysAutoResize)) {
		// Popup content
		ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
			"Realizzato da Michele Berni 4D(sa) Corso Scienze Applicate - A.S. 2024/2025");
		ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
			"Per gli open day del liceo scientifico A. Oriani di Ravenna");
		ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
			"Il progetto e' open source e disponibile su GitHub");
		ImGui::EndPopup();
	}	
}

void UIManager::displayLicenseMenu() {
	ImGui::SetNextWindowSize(ImVec2(1000, 445), ImGuiCond_Once);

	ImGui::OpenPopup("Licenza");
	if (ImGui::BeginPopupModal("Licenza", &showLicenseMenu, ImGuiWindowFlags_NoResize)) {
		// CC BY-NC-SA License

		ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);

		ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "CC BY-NC-SA License");
		ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
			"This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.\nYou are free to:\n"
			"- Share: copy and redistribute the material in any medium or format\n"
			"- Adapt: remix, transform, and build upon the material\n"
			"Under the following terms:\n"
			"- Attribution: You must give appropriate credit, provide a link to the license, and indicate if changes were made.\n"
			"- NonCommercial: You may not use the material for commercial purposes.\n"
			"- ShareAlike: If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.\n"
			"No additional restrictions: You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits."
			"For more details, see the full license text at:"
			);

		if (ImGui::Button("https://creativecommons.org/licenses/by-nc-sa/4.0/", ImVec2(ImGui::GetContentRegionAvail().x, 30))) {
			// Open the license link in the default web browser
			system("start https://creativecommons.org/licenses/by-nc-sa/4.0/");
		}

		ImGui::PopTextWrapPos();
		ImGui::EndPopup();
	}
}

void UIManager::displayPopUp() {
	ImGui::OpenPopup("Attenzione");
	if (ImGui::BeginPopupModal("Attenzione", &showPopUpMenu, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::TextColored(messageColor, popUpMessage.c_str());
		ImGui::EndPopup();
	}
}

void UIManager::displayTutorialMenu() {
	ImGui::SetNextWindowSize(ImVec2(1660, 440), ImGuiCond_Once);

	ImGui::OpenPopup("Tutorial");
	if (ImGui::BeginPopupModal("Tutorial", &showTutorialMenu, ImGuiWindowFlags_NoResize)) {
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
		ImGui::EndPopup();
	}
}