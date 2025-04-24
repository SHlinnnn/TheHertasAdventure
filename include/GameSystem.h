#pragma once
#include "Player.h"
#include "Enemy.h"

class GameSystem {
    Player* player;
    Difficulty difficulty;
    int currentStage = 1;
    
    void showPathSelection();
    void handleCombat();
    void handleEvent();
    void handleShop();
    void calculateAttackRounds();
    
public:
    void startGame();
    void mainLoop();
};
