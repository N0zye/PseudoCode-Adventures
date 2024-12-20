#pragma once

// Legend
// 0 - Empty
// 1 - Wall
// 2 - Key
// 3 - Closed Door
// 4 - Open Door
// 5 - Exit
// 6 - Player spawnpoint

class Level {
public:
    std::string name;
    std::vector<std::vector<int>> grid;
    Level(std::string name, std::vector<std::vector<int>> grid) : name(name), grid(grid) {}
};

// Default level will be loaded if reading from file fails
inline const std::string defaultLevelName = "Default level";

inline std::vector<std::vector<int>> defaultLevelGrid = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 5, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 3, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 6, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

inline Level defaultLevel(defaultLevelName, defaultLevelGrid);