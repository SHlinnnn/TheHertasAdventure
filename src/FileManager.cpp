#include "FileManager.h"
#include <fstream>
#include <stdexcept>

struct SaveData {
    Path path;
    Difficulty difficulty;
    int currentStage;
    int bonusHP;
    int bonusATK;
    int bonusSPD;
    int gold;
    bool hasResurrection;
};

bool FileManager::saveGame(const Player& player, int stage, 
                          const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return false;

    SaveData data{
        player.chosenPath,
        player.difficulty,
        stage,
        player.bonusHP,
        player.bonusATK,
        player.bonusSPD,
        player.gold,
        player.hasResurrection
    };

    file.write(reinterpret_cast<const char*>(&data), sizeof(SaveData));
    return file.good();
}

bool FileManager::loadGame(Player& player, int& stage, 
                          const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    SaveData data;
    file.read(reinterpret_cast<char*>(&data), sizeof(SaveData));
    
    if (file.gcount() != sizeof(SaveData)) {
        return false;
    }

    player = Player(data.path);
    player.bonusHP = data.bonusHP;
    player.bonusATK = data.bonusATK;
    player.bonusSPD = data.bonusSPD;
    player.gold = data.gold;
    player.hasResurrection = data.hasResurrection;
    stage = data.currentStage;
    
    return true;
}
