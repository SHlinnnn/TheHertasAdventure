#include "GameSystem.h"
#include <iostream>
#include <limits>

void GameSystem::startGame(Difficulty diff) {
    difficulty = diff;
    currentStage = 1;
    player = new Player(Path::DESTRUCTION, diff); // 默认命途，实际应由玩家选择
}

void GameSystem::mainLoop() {
    while (currentStage <= 13) {
        try {
            handleCombat();
            currentStage++;
        } catch (const std::exception& e) {
            std::cerr << "游戏结束: " << e.what() << std::endl;
            break;
        }
    }
    
    if (currentStage > 13) {
        std::cout << "\n★★★★★ 恭喜通关！ ★★★★★\n";
    }
}

void GameSystem::handleCombat() {
    // 商店触发逻辑
    if (currentStage == 5 || currentStage == 9 || currentStage == 13) {
        handleShop();
    }

    Enemy enemy(currentStage, difficulty);
    Player& p = *player;
    
    std::cout << "\n===== 第 " << currentStage << " 关 =====" << std::endl;
    enemy.printStats();
    p.printStatus();

    // 速度机制计算
    int playerAttacks = 1, enemyAttacks = 1;
    if (p.getFinalSPD() > enemy.spd) {
        playerAttacks = p.getFinalSPD() / enemy.spd;
    } else {
        enemyAttacks = enemy.spd / p.getFinalSPD();
    }

    // 战斗循环
    while (enemy.hp > 0 && p.getFinalHP() > 0) {
        // 玩家攻击阶段
        for (int i = 0; i < playerAttacks && enemy.hp > 0; ++i) {
            int damage = p.getFinalATK();
            enemy.hp -= damage;
            std::cout << "→ 造成 " << damage << " 点伤害，敌人剩余生命: " 
                     << std::max(enemy.hp, 0) << std::endl;
        }

        // 敌人攻击阶段
        if (enemy.hp > 0) {
            for (int i = 0; i < enemyAttacks && p.getFinalHP() > 0; ++i) {
                int damage = enemy.atk;
                p.baseHP -= damage;
                std::cout << "← 受到 " << damage << " 点伤害，剩余生命: " 
                         << p.getFinalHP() << std::endl;
            }
        }
    }

    // 战斗结果处理
    if (p.getFinalHP() <= 0) {
        if (p.hasResurrection) {
            p.useResurrection();
            std::cout << "\n再创世！\n";
        } else {
            throw std::runtime_error("战斗失败");
        }
    }

    // 战后处理
    p.gold += 50;
    std::cout << "获得50金币，当前总计: " << p.gold << std::endl;
}
