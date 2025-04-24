#include "EventSystem.h"
#include <random>
#include <cmath>
#include <iostream>

EventSystem::Result EventSystem::trigger(Player& player, int stage) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> prob{20, 45, 20, 10, 5};
    
    switch(prob(gen)) {
        case NOTHING:
            return NOTHING;
            
        case STAT_UP: {
            int value = 15 + std::round(stage * 1.5);
            std::uniform_int_distribution<> stat(0, 2);
            switch(stat(gen)) {
                case 0: player.applyBlessing(value, 0, 0); break;
                case 1: player.applyBlessing(0, value, 0); break;
                case 2: player.applyBlessing(0, 0, value); break;
            }
            return STAT_UP;
        }
        
        case STAT_DOWN: {
            int penalty = 10 + stage * 2;
            player.applyBlessing(-penalty, -penalty/2, -penalty/2);
            return STAT_DOWN;
        }
        
        case HARD_BATTLE: {
            std::cout << "虚空裂缝中涌出恐怖的虫群...\n";
            return HARD_BATTLE;
        }
            
        case RESURRECTION:
            if (!player.hasResurrection) {
                player.hasResurrection = true;
            }
            return RESURRECTION;
    }
    return NOTHING;
}
