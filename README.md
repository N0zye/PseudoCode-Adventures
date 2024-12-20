# Pseudocode Adventures

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/eef51b1c3c6f4b5ab0da7ecdb02bb170)](https://app.codacy.com/gh/N0zye/PseudoCode-Adventures?utm_source=github.com&utm_medium=referral&utm_content=N0zye/PseudoCode-Adventures&utm_campaign=Badge_Grade)

Pseudocode Adventures is an interactive game developed in C++ for the open days of Liceo Scientifico Statale Alfredo Oriani in Ravenna, RA. The game introduces players to basic programming concepts by combining engaging gameplay with real-time scripting mechanics. Players will solve challenges, navigate obstacles, and interact with the game world by writing pseudocode commands that control the main character's actions.

## Features
- **Split-Screen Interface**: Gameplay on the left, scripting on the right.
- **Interactive Scripting**: Write and execute pseudocode in real-time to solve puzzles and progress through levels.
- **Dynamic Levels**: Each level is a 10x10 grid of integers, representing various terrain types and objectives, loaded dynamically from JSON files.
- **Event-Driven Design**: Utilizes an EventBus to handle UI and game interactions seamlessly.
- **Educational Focus**: Designed to teach fundamental programming concepts in a fun and engaging way.

## Technology Stack
The game is built using the following libraries and frameworks:

- **[SFML](https://www.sfml-dev.org/)**: Simple and Fast Multimedia Library for 2D graphics, input handling, and window management.
- **[Dear ImGui](https://github.com/ocornut/imgui)**: A bloat-free graphical user interface library.
- **[imgui-SFML](https://github.com/eliasdaler/imgui-sfml)**: Bindings to integrate Dear ImGui with SFML.
- **[nlohmann/json](https://github.com/nlohmann/json)**: A modern C++ library for JSON parsing and serialization.

## How to Build

### Prerequisites
Ensure you have the following tools installed:
- Visual Studio (2019 or higher) with C++ development tools.
  
### Build Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/pseudocode-adventures.git
   cd pseudocode-adventures
   ```
2. Open the solution file:
   - Navigate to the project directory and open `PseudocodeAdventures.sln` in Visual Studio.
3. Build the project:
   - Set the build configuration to `Release` or `Debug` as needed.
   - Press `Ctrl+Shift+B` to build the solution.
4. Run the game:
   - Press `F5` to start debugging or navigate to the output directory to run the executable.

## Usage
- **Controls**: Use the scripting panel to write pseudocode and execute it to control the character.
- **Editing Levels**: Levels can be modified by editing the JSON files in the `levels/` directory.

## Credits
This project utilizes the following libraries:
- **SFML** by Laurent Gomila and contributors ([License](https://www.sfml-dev.org/license.php)).
- **Dear ImGui** by Omar Cornut and contributors ([License](https://github.com/ocornut/imgui/blob/master/LICENSE.txt)).
- **imgui-SFML** by Elias Daler ([License](https://github.com/SFML/imgui-sfml/blob/master/LICENSE)).
- **nlohmann/json** by Niels Lohmann ([License](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT)).

## License
This project is licensed under the **MIT** license. Please see the `LICENSE` file for details.
