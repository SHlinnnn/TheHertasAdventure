#include "FileManager.h"
#include <fstream>

#pragma pack(push, 1)
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
#pragma pack(pop)

bool FileManager::save(const Player& player, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return false;

    SaveData data{
        player.chosenPath,
        player.difficulty,
        player.currentStage,
        player.bonusHP,
        player.bonusATK,
        player.bonusSPD,
        player.gold,
        player.hasResurrection
    };

    file.write(reinterpret_cast<const char*>(&data), sizeof(SaveData));
    return file.good();
}

bool FileManager::load(Player& player, std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    SaveData data;
    file.read(reinterpret_cast<char*>(&data), sizeof(SaveData));
    
    if (file.gcount() != sizeof(SaveData)) return false;

    player = Player(data.path, data.difficulty);
    player.bonusHP = data.bonusHP;
    player.bonusATK = data.bonusATK;
    player.bonusSPD = data.bonusSPD;
    player.gold = data.gold;
    player.hasResurrection = data.hasResurrection;
    player.currentStage = data.currentStage;
    
    return true;
}
