#include "Enemy.h"
#include <random>
#include <cmath>

void Enemy::generateName(int stage) {
    std::string prefixes[] = {"幼年", "成年", "精英"};
    std::string types[] = {"虚数兽", "反物质兽", "星轨兽"};
    
    std::random_device rd;
    std::mt19937 gen(rd());
    name = prefixes[stage % 3] + types[stage % 3];
}

void Enemy::scaleStats(int stage, Difficulty diff) {
    hp = 80 + stage*20 + static_cast<int>(diff)*30;
    atk = 20 + stage*10 + static_cast<int>(diff)*15;
    spd = 50 + stage*5 + static_cast<int>(diff)*10;
}
