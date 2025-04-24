#include "GameSystem.h"
#include "Enemy.h"
#include "Blessing.h"
#include "EventSystem.h"
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// 核心战斗系统 
void GameSystem::handleCombat() {
    Enemy enemy(currentStage, difficulty);
    Player& player = *this->player;

    cout << "\n第 " << currentStage << " 关\n";
    enemy.printStats();
    player.printStatus();

    // 速度机制计算
    int playerSpeed = player.getFinalSPD();
    int enemySpeed = enemy.spd;
    int playerAttacks = 1, enemyAttacks = 1;

    if (playerSpeed > enemySpeed) {
        playerAttacks = floor(playerSpeed / enemySpeed);
        cout << "✦ 速度优势！你将攻击 " << playerAttacks << " 次！\n";
    } else {
        enemyAttacks = floor(enemySpeed / playerSpeed);
        cout << "⚠ 敌人速度更快！将攻击 " << enemyAttacks << " 次！\n";
    }

    // 战斗循环
    while (enemy.hp > 0 && player.getFinalHP() > 0) {
        // 玩家攻击阶段
        for (int i = 0; i < playerAttacks; ++i) {
            int damage = player.getFinalATK();
            enemy.hp -= damage;
            cout << "→ 你对敌人造成 " << damage << " 点伤害！\n";
            if (enemy.hp <= 0) break;
        }

        // 敌人攻击阶段 
        if (enemy.hp > 0) {
            for (int i = 0; i < enemyAttacks; ++i) {
                int damage = enemy.atk;
                player.baseHP -= damage;
                cout << "← 敌人对你造成 " << damage << " 点伤害！\n";
                if (player.getFinalHP() <= 0) break;
            }
        }
    }

    // 战斗结果处理
    if (player.getFinalHP() <= 0) {
        if (player.hasResurrection) {
            cout << "\n 再创世！\n";
            player.useResurrection();
            cout << "生命值恢复至 100！\n";
            enemy.hp = 0; // 强制胜利
        } else {
            throw runtime_error("战斗失败");
        }
    }

    // 战后处理
    player.gold += 50;
    cout << "\n获得 50 金币（当前总计：" << player.gold << "）\n";

    // 商店触发逻辑（第5/9关前）
    if ((currentStage == 4 || currentStage == 8) && !player.hasVisitedShop) {
        handleShop();
        player.hasVisitedShop = true;
    }
}

//商店系统
void GameSystem::handleShop() {
    vector<Blessing> blessings = BlessingSystem::getShopBlessings(currentStage);
    
    cout << "\n══════════ 星际商店 ══════════\n";
    for (size_t i = 0; i < blessings.size(); ++i) {
        cout << i+1 << ". " << blessings[i].name 
             << " (价格：" << blessings[i].cost << " 金币)\n"
             << "   → 生命+" << blessings[i].hpBonus 
             << " 攻击+" << blessings[i].atkBonus
             << " 速度+" << blessings[i].spdBonus << endl;
    }
    cout << "0. 离开商店\n";

    while (true) {
        int choice;
        cout << "\n当前金币：" << player->gold << "\n选择：";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) break;
        if (choice < 1 || choice > static_cast<int>(blessings.size())) {
            cout << "无效选择！";
            continue;
        }

        Blessing selected = blessings[choice-1];
        if (player->gold >= selected.cost) {
            BlessingSystem::applyBlessing(*player, selected);
            player->gold -= selected.cost;
            cout << "购买成功！已装备 " << selected.name << endl;
        } else {
            cout << "金币不足！\n";
        }
    }
}
