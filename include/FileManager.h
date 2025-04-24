#pragma once
#include <string>
#include "Player.h"

class FileManager {
public:
    static bool save(const Player& player, const std::string& filename);
    static bool load(Player& player, std::string& filename);
};
