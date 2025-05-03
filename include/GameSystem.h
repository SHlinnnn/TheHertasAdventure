#pragma once
#include "Player.h"
#include "Enemy.h"

class GameSystem {
    Player* player;
    int currentStage;  // 从Player初始化
    void handleCombat();
    void handleShop();
    void handleEvent();

public:
    explicit GameSystem(Player* player);
    void run();
    int getCurrentStage() const;
private:
    void handleVictoryBlessing();
};
