#include "GameSystem.h"
#include "Enemy.h"
#include "Blessing.h"
#include "EventSystem.h"
#include <iostream>
#include <limits>

GameSystem::GameSystem(Player* player) : player(player) {}

void GameSystem::run() {
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
        std::cout << "\n★★★★★ 通关成功！ ★★★★★\n";
    }
}

void GameSystem::handleCombat() {
    if (currentStage == 5 || currentStage == 9 || currentStage == 13) {
        handleShop();
    }

    Enemy enemy(currentStage, player->difficulty);
    Player& p = *player;
    
    std::cout << "\n===== 第 " << currentStage << " 关 =====" << std::endl;
    enemy.printStats();
    p.printStatus();

    // 速度机制
    int playerAttacks = 1;
    int enemyAttacks = 1;
    if (p.getFinalSPD() > enemy.spd) {
        playerAttacks = p.getFinalSPD() / enemy.spd;
    } else {
        enemyAttacks = enemy.spd / p.getFinalSPD();
    }

    // 战斗循环
    while (enemy.hp > 0 && p.getFinalHP() > 0) {
        // 玩家攻击
        for (int i = 0; i < playerAttacks; ++i) {
            int damage = p.getFinalATK();
            enemy.hp -= damage;
            std::cout << "→ 造成 " << damage << " 点伤害，敌人剩余: " 
                     << std::max(enemy.hp, 0) << std::endl;
            if (enemy.hp <= 0) break;
        }

        // 敌人攻击
        if (enemy.hp > 0) {
            for (int i = 0; i < enemyAttacks; ++i) {
                int damage = enemy.atk;
                p.baseHP -= damage;
                std::cout << "← 受到 " << damage << " 点伤害，剩余生命: " 
                         << p.getFinalHP() << std::endl;
                if (p.getFinalHP() <= 0) break;
            }
        }
    }

    // 战斗结果
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
    
    // 处理事件
    handleEvent();
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
