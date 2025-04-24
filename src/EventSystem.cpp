#include "EventSystem.h"
#include <random>

void EventSystem::triggerRandomEvent(Player& player, int stage) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> prob{20, 45, 20, 10, 5};
    
    switch(prob(gen)) {
    case STAT_BOOST: {
        std::uniform_int_distribution<> stat(0,2);
        int value = 10 + stage*5;
        // 增强逻辑
        break;
    }
    case ELITE_BATTLE:
        // 生成强化敌人
        break;
    case RESURRECTION:
        player.hasResurrection = true;
        std::cout << "获得神秘祝福【再创世】!\n";
        break;
    }
}
