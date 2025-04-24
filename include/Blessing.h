#pragma once
#include <vector>
#include <string>
#include "Player.h"

struct Blessing {
    std::string name;
    int hp;
    int atk;
    int spd;
    int cost;
};

class BlessingSystem {
public:
    static std::vector<Blessing> getShopBlessings(int stage);
    static void apply(Player& player, const Blessing& blessing);
};
