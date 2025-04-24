#include "GameSystem.h"
#include <iostream>

void GameSystem::handleCombat() {
    Enemy enemy(currentStage, difficulty);
    
    std::cout << "\n=== 第 " << currentStage << " 关 ===";
    enemy.printStats();
    player->printStatus();
    
    calculateAttackRounds();
    
    // 战斗胜利逻辑
    player->gold += 50;
    if(currentStage % 4 == 1 && currentStage != 1) {
        handleShop();
    }
}

void GameSystem::calculateAttackRounds() {
    int playerSPD = player->getFinalSPD();
    int enemySPD = enemy.spd;
    
    if(playerSPD > enemySPD) {
        int rounds = playerSPD / enemySPD;
        std::cout << "我方速度优势! 你将攻击 " << rounds << " 次!\n";
    } else {
        int rounds = enemySPD / playerSPD;
        std::cout << "敌人速度更快! 将攻击 " << rounds << " 次!\n";
    }
}
