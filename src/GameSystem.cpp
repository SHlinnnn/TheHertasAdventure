#include "GameSystem.h"  
#include "FileManager.h"  
#include "Enemy.h"  
#include "Blessing.h"  
#include "EventSystem.h"  
#include <iostream>  
#include <limits>  

// Constructor  
GameSystem::GameSystem(Player* player)   
    : player(player), currentStage(player->currentStage) {}  

void GameSystem::handleVictoryBlessing() {  
    auto blessings = BlessingSystem::getShopBlessings(currentStage);  
    for (auto& bless : blessings) { bless.cost = 0; }  

    std::cout << "\n=== Choose a Blessing ===\n";  
    for (size_t i = 0; i < blessings.size(); ++i) {  
        std::cout << i+1 << ". " << blessings[i].name   
                 << " (+HP:" << blessings[i].hp  
                 << " +ATK:" << blessings[i].atk  
                 << " +SPD:" << blessings[i].spd << ")\n";  
    }  

    int choice;  
    while (true) {  
        std::cout << "Choice (1-" << blessings.size() << "): ";  
        if (std::cin >> choice && choice >= 1 && choice <= static_cast<int>(blessings.size())) {  
            BlessingSystem::apply(*player, blessings[choice-1]);  
            break;  
        }  
        std::cin.clear();  
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
    }  
}  

void GameSystem::run() {  
    while (currentStage <= 13) {  
        std::cout << "\n===== Stage " << currentStage << " =====" << std::endl;  
          
        // Save option  
        std::cout << "0. Save & Exit\n";  
        std::cout << "Choose action:\n"  
                  << "1. Explore Event\n"  
                  << "2. Engage Combat\n";  

        int choice;  
        while (true) {  
            std::cout << "Input (0-2): ";  
            if (std::cin >> choice) {  
                if (choice == 0) {  
                    player->currentStage = currentStage; // Sync stage  
                    std::string filename;  
                    std::cout << "Enter save filename: ";  
                    std::cin >> filename;  
                    if (FileManager::save(*player, filename)) {  
                        std::cout << "Saved successfully!\n";  
                    } else {  
                        std::cout << "Save failed!\n";  
                    }  
                    return; // Exit loop  
                }  
                if (choice == 1 || choice == 2) break;  
            }  
            std::cin.clear();  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
        }  

        // Key stage combat  
        if (currentStage == 1 || currentStage == 5 || currentStage == 9 || currentStage == 13) {  
            handleCombat();  
        }   
        // Normal stage  
        else {  
            if (choice == 1) {  
                handleEvent();  
            } else if (choice == 2) {  
                handleCombat();  
            }  
        }  
          
        currentStage++;  
        player->currentStage = currentStage; // Update stage  
    }  
      
    if (currentStage > 13) {  
        std::cout << "\n★★★★★ Stage Clear! ★★★★★\n";  
    }  
}  

void GameSystem::handleCombat() {  
    if (currentStage == 5 || currentStage == 9 || currentStage == 13) {  
        handleShop();  
    }  

    Enemy enemy(currentStage, player->difficulty);  
    Player& p = *player;  
      
    std::cout << "\n====== Combat Start ======\n";  
    enemy.printStats();  
    p.printStatus();  

    // SPD mechanism  
    int playerSPD = p.getFinalSPD();  
    int enemySPD = enemy.spd;  
    int playerAttacks = 1, enemyAttacks = 1;  

    if (playerSPD > enemySPD) {  
        playerAttacks = playerSPD / enemySPD;  
        std::cout << "\n✦ SPD Advantage! You attack " << playerAttacks << " times!\n";  
    } else if (enemySPD > playerSPD) {  
        enemyAttacks = enemySPD / playerSPD;  
        std::cout << "\n⚠ Enemy SPD Higher! Attacks " << enemyAttacks << " times!\n";  
    } else {  
        std::cout << "\n⚔ SPD Equal!\n";  
    }  

    // Combat loop  
    while (enemy.hp > 0 && p.getFinalHP() > 0) {  
        // Player attack  
        for (int i = 0; i < playerAttacks; ++i) {  
            int damage = p.getFinalATK();  
            enemy.hp -= damage;  
            std::cout << "[Attack" << i+1 << "] → Dealt " << damage   
                      << " damage. Enemy HP: " << std::max(enemy.hp, 0) << "\n";  
            if (enemy.hp <= 0) break;  
        }  

        // Enemy attack  
        if (enemy.hp > 0) {  
            for (int i = 0; i < enemyAttacks; ++i) {  
                int damage = enemy.atk;  
                p.baseHP -= damage;  
                std::cout << "[Hit" << i+1 << "] ← Took " << damage   
                          << " damage. Your HP: " << p.getFinalHP() << "\n";  
                if (p.getFinalHP() <= 0) break;  
            }  
        }  
    }  

    // Result  
    if (p.getFinalHP() <= 0) {  
        if (p.hasResurrection) {  
            p.useResurrection();  
            std::cout << "\nResurrected!\n";  
        } else {  
            throw std::runtime_error("Combat Failed");  
        }  
    }  

    p.gold += 50;  
    std::cout << "Gained 50 Gold. Total: " << p.gold << std::endl;  
    if (player->getFinalHP() > 0) {  
        if (currentStage != 13) {  
            handleVictoryBlessing();  
        }  
    }  
}  

void GameSystem::handleShop() {  
    auto blessings = BlessingSystem::getShopBlessings(currentStage);  
      
    std::cout << "\n=== Star Market ===\n"<<"Current Gold: "<<player->gold<<"\n";  
    for (size_t i = 0; i < blessings.size(); ++i) {  
        std::cout << i+1 << ". " << blessings[i].name   
                 << " (" << blessings[i].cost << " Gold)"  
                 << " +HP:" << blessings[i].hp  
                 << " +ATK:" << blessings[i].atk  
                 << " +SPD:" << blessings[i].spd << "\n";  
    }  
      
    while (true) {  
        int choice;  
        std::cout << "\nChoice (0 to leave): ";  
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
            std::cout << "Purchased: " << selected.name << "\n";  
        } else {  
            std::cout << "Insufficient Gold!\n";  
        }  
    }  
}  

void GameSystem::handleEvent() {  
    auto result = EventSystem::trigger(*player, currentStage);  
    switch (result) {  
        case EventSystem::NOTHING:  
            std::cout << "Nothing happened...\n";  
            break;  
        case EventSystem::STAT_UP:  
            std::cout << "Stats increased!\n";  
            break;  
        case EventSystem::STAT_DOWN:  
            std::cout << "Stats decreased!\n";  
            break;  
        case EventSystem::HARD_BATTLE: {  
            Enemy eliteEnemy(currentStage, player->difficulty);  
            eliteEnemy.name = "Swarm: Propagation";  
            eliteEnemy.hp *= 3;  // Triple HP  
            eliteEnemy.atk += 30; // ATK boost  
              
            std::cout << "\n███ Encountered " << eliteEnemy.name << "! ███\n";  
            std::cout << "HP:" << eliteEnemy.hp << " ATK:" << eliteEnemy.atk << "\n";  

            // Force combat  
            int originalHP = player->baseHP;  
            player->baseHP = player->getFinalHP(); // Save HP  
            try {  
                handleCombat();  
                player->applyBlessing(30, 20, 15); // Victory bonus  
                std::cout << "Victory! Stats boosted!\n";  
            } catch (...) {  
                player->baseHP = originalHP; // Restore HP  
                throw std::runtime_error("The Swarm consumed you...");  
            }  
            break;  
        }  
        case EventSystem::RESURRECTION:  
            std::cout << "Blessing gained: Resurrection!\n";  
            break;  
        default:  
            std::cout << "Unknown event\n";  
            break;  
    }  
}  

int GameSystem::getCurrentStage() const {  
    return currentStage;  
