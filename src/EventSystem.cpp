#include "EventSystem.h"
#include <random>
#include <cmath>

void EventSystem::triggerRandomEvent(Player& player, int stage) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> prob{20, 45, 20, 10, 5};
    
    switch(prob(gen)) {
        case NOTHING:
            std::cout << "\n什么也没有发生...\n";
            break;
            
        case STAT_BOOST: {
            std::uniform_int_distribution<> statDist(0, 2);
            int value = 15 + std::round(stage * 1.5);
            switch(statDist(gen)) {
                case 0: 
                    player.applyBlessing(value, 0, 0);
                    std::cout << "生命值永久增加 " << value << " 点！\n";
                    break;
                case 1:
                    player.applyBlessing(0, value, 0);
                    std::cout << "攻击力永久增加 " << value << " 点！\n";
                    break;
                case 2:
                    player.applyBlessing(0, 0, value);
                    std::cout << "速度永久增加 " << value << " 点！\n";
                    break;
            }
            break;
        }
        
        case STAT_REDUCE: {
            int penalty = 10 + stage * 2;
            player.applyBlessing(-penalty, -penalty/2, -penalty/2);
            std::cout << "所有属性暂时降低！\n";
            break;
        }
        
        case ELITE_BATTLE: {
            std::cout << "\n遭遇精英敌人！\n";
            // 触发强化战斗逻辑
            break;
        }
        
        case RESURRECTION:
            if (!player.hasResurrection) {
                player.hasResurrection = true;
                std::cout << "\n获得星神秘礼【再创世】！\n";
            }
            break;
    }
}
