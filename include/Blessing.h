#pragma once
#include <string>
#include <vector>
#include "Player.h"

struct Blessing {
    std::string name;
    int hpBonus;
    int atkBonus;
    int spdBonus;
    int cost;
};

class BlessingSystem {
public:
    static std::vector<Blessing> getShopBlessings(int currentStage);
    static void applyBlessing(Player& player, const Blessing& blessing);
};
