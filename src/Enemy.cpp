#include "Enemy.h"  
#include <random>  
#include <cmath>  
#include <iostream>  

Enemy::Enemy(int stage, Difficulty diff) {  
    generateName(stage);  
    scaleStats(stage, diff);  
}  

void Enemy::generateName(int stage) {  
    std::string prefixes[] = {"Juvenile", "Adult", "Elite"};  
    std::string types[] = {"Void Beast", "Antimatter Beast", "Stellar Beast"};  
      
    std::random_device rd;  
    std::mt19937 gen(rd());  
    name = prefixes[stage % 3] + " " + types[stage % 3];  
}  

void Enemy::scaleStats(int stage, Difficulty diff) {  
    hp = 80 + stage*20 + static_cast<int>(diff)*30;  
    atk = 20 + stage*10 + static_cast<int>(diff)*15;  
    spd = 50 + stage*5 + static_cast<int>(diff)*10;  
}  

void Enemy::printStats() const {  
    std::cout << "\n=== Enemy Stats ===\n"  
              << "Name: " << name << "\n"  
              << "HP: " << hp << "\n"  
              << "ATK: " << atk << "\n"  
              << "SPD: " << spd << "\n";  
}  
