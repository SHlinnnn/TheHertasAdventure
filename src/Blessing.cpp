#include <vector>

std::vector<Blessing> BlessingSystem::getShopBlessings(int currentStage) {
    int priceMultiplier = 1 + currentStage/5;
    
    return {
        {"丰檀生薪", 30, 0, 0, 80 * priceMultiplier},
        {"激变变星", 0, 25, 0, 100 * priceMultiplier},
        {"狩星巡日", 0, 0, 40, 120 * priceMultiplier},
        {"均衡增幅", 15, 15, 15, 150 * priceMultiplier}
    };
}

void BlessingSystem::applyBlessing(...) {
    player.applyBlessing(...);
}
