#include "EventSystem.h"
#include <random>
#include "Player.h"

void EventSystem::triggerRandomEvent(Player& player, int stage) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> prob{20, 45, 20, 10, 5};
    
    switch(prob(gen)) {
        // ... 其他case不变
        
        case RESURRECTION:  // [MODIFIED] 新增专属逻辑
            if (!player.hasResurrection) {
                player.hasResurrection = true;
                std::cout << "■■■ 获得星神秘礼【再创世】！■■■\n"
                          << "效果：死亡后可复活一次，恢复全部生命\n";
            } else {
                std::cout << "神秘力量已存在，转化为生命强化！\n";
                player.applyBlessing(50, 0, 0);
            }
            break;
    }
}
