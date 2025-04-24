#include "GameSystem.h"
#include "Enemy.h"
#include "Blessing.h"
#include "EventSystem.h"
#include <iostream>
#include <limits>

GameSystem::GameSystem(Player* player) : player(player) {}

void GameSystem::handleVictoryBlessing() {
    auto blessings = BlessingSystem::getShopBlessings(currentStage);
    for (auto& bless : blessings) {
        bless.cost = 0;
    }

    std::cout << "\n=== 请选择祝福 ===\n";
    for (size_t i = 0; i < blessings.size(); ++i) {
        std::cout << i+1 << ". " << blessings[i].name 
                 << " (+HP:" << blessings[i].hp
                 << " +ATK:" << blessings[i].atk
                 << " +SPD:" << blessings[i].spd << ")\n";
    }

    int choice;
    while (true) {
        std::cout << "选择 (1-" << blessings.size() << "): ";
        if (std::cin >> choice && choice >= 1 && choice <= static_cast<int>(blessings.size())) {
            BlessingSystem::apply(*player, blessings[choice-1]);
            std::cout << "已获得「" << blessings[choice-1].name << "」\n";
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void GameSystem::run() {
    while (currentStage <= 13) {
        std::cout << "\n===== 第 " << currentStage << " 关 =====" << std::endl;
        
        // 关键关卡强制战斗
        if (currentStage == 1 || currentStage == 5 || currentStage == 9 || currentStage == 13) {
            handleCombat();
        } 
        // 普通关卡提供选择
        else {
            std::cout << "选择行动：\n"
                      << "1. 探索事件\n"
                      << "2. 主动战斗\n";
            
            int choice;
            while (true) {
                std::cin >> choice;
                if (choice == 1) {
                    handleEvent();
                    break;
                } else if (choice == 2) {
                    handleCombat();
                    break;
                }
                std::cout << "无效输入，请重新选择 (1-2): ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        
        currentStage++;
    }
    
    if (currentStage > 13) {
        std::cout << "\n★★★★★ 通关成功！ ★★★★★\n";
    }
}

void GameSystem::handleCombat() {
    if (currentStage == 5 || currentStage == 9 || currentStage == 13) {
        handleShop();
    }

    Enemy enemy(currentStage, player->difficulty);
    Player& p = *player;
    
    std::cout << "\n====== 战斗开始 ======\n";
    enemy.printStats();
    p.printStatus();

    //速度机制
    int playerSPD = p.getFinalSPD();
    int enemySPD = enemy.spd;
    int playerAttacks = 1, enemyAttacks = 1;

    if (playerSPD > enemySPD) {
        playerAttacks = playerSPD / enemySPD;
        std::cout << "\n✦ 速度优势! 你将攻击 " << playerAttacks << " 次!\n";
    } else if (enemySPD > playerSPD) {
        enemyAttacks = enemySPD / playerSPD;
        std::cout << "\n⚠ 敌人速度更快! 将攻击 " << enemyAttacks << " 次!\n";
    } else {
        std::cout << "\n⚔ 双方速度相同!\n";
    }

    //战斗循环
    while (enemy.hp > 0 && p.getFinalHP() > 0) {
        // 玩家攻击阶段
        for (int i = 0; i < playerAttacks; ++i) {
            int damage = p.getFinalATK();
            enemy.hp -= damage;
            std::cout << "[攻击" << i+1 << "] → 造成 " << damage 
                      << " 伤害，敌人剩余: " << std::max(enemy.hp, 0) << "\n";
            if (enemy.hp <= 0) break;
        }

        // 敌人攻击阶段
        if (enemy.hp > 0) {
            for (int i = 0; i < enemyAttacks; ++i) {
                int damage = enemy.atk;
                p.baseHP -= damage;
                std::cout << "[受击" << i+1 << "] ← 受到 " << damage 
                          << " 伤害，剩余生命: " << p.getFinalHP() << "\n";
                if (p.getFinalHP() <= 0) break;
            }
        }
    }

    //战斗结果处理
    if (p.getFinalHP() <= 0) {
        if (p.hasResurrection) {
            p.useResurrection();
            std::cout << "\n再创世!\n";
        } else {
            throw std::runtime_error("战斗失败");
        }
    }

    p.gold += 50;
    std::cout << "获得50金币，当前总计: " << p.gold << std::endl;
    if (player->getFinalHP() > 0) {
        handleVictoryBlessing();
    }
}


void GameSystem::handleShop() {
    auto blessings = BlessingSystem::getShopBlessings(currentStage);
    
    std::cout << "\n=== 星际商店 ===\n";
    for (size_t i = 0; i < blessings.size(); ++i) {
        std::cout << i+1 << ". " << blessings[i].name 
                 << " (" << blessings[i].cost << "金币)"
                 << " +HP:" << blessings[i].hp
                 << " +ATK:" << blessings[i].atk
                 << " +SPD:" << blessings[i].spd << "\n";
    }
    
    while (true) {
        int choice;
        std::cout << "\n选择 (0离开): ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        if (choice == 0) break;
        if (choice < 1 || choice > static_cast<int>(blessings.size())) {
            continue;
        }
        
        Blessing selected = blessings[choice-1];
        if (player->gold >= selected.cost) {
            BlessingSystem::apply(*player, selected);
            player->gold -= selected.cost;
            std::cout << "购买成功: " << selected.name << "\n";
        } else {
            std::cout << "金币不足！\n";
        }
    }
}

// 修改src/GameSystem.cpp的handleEvent函数
void GameSystem::handleEvent() {
    auto result = EventSystem::trigger(*player, currentStage);
    switch (result) {
        case EventSystem::NOTHING:
            std::cout << "平安无事...\n";
            break;
        case EventSystem::STAT_UP:
            std::cout << "获得属性提升！\n";
            break;
        case EventSystem::STAT_DOWN:
            std::cout << "属性暂时下降！\n";
            break;
        case EventSystem::HARD_BATTLE:
            std::cout << "遭遇强敌！\n";
            break;
        case EventSystem::RESURRECTION:
            std::cout << "获得神秘复活祝福！\n";
            break;
        default:
            std::cout << "未知事件\n";
            break;
    }
}

int GameSystem::getCurrentStage() const {
    return currentStage;
}
