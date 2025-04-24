#pragma once
#include "Player.h"
#include <string>

class FileManager {
public:
    static bool saveGame(const Player& player, int currentStage, 
                        const std::string& filename);
    static bool loadGame(Player& player, int& currentStage,
                        const std::string& filename);
};
