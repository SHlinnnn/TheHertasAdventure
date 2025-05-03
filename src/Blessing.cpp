#include "Blessing.h"  

std::vector<Blessing> BlessingSystem::getShopBlessings(int Stage) {  
    int priceMultiplier = 1 + Stage/5;  
      
    return {  
        {"Bountiful Wood", 30, 0, 0, 80 * priceMultiplier},  
        {"Stellar Surge", 0, 25, 0, 100 * priceMultiplier},  
        {"Celestial Hunt", 0, 0, 40, 120 * priceMultiplier},  
        {"Harmonic Boost", 15, 15, 15, 150 * priceMultiplier}  
    };  
}  

void BlessingSystem::apply(Player& player, const Blessing& blessing) {  
    player.applyBlessing(blessing.hp, blessing.atk, blessing.spd);  
}  
