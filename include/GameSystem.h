#pragma once
#include "Player.h"
#include "Enemy.h"

class GameSystem {
    Player* player;
    Difficulty difficulty;
    int currentStage = 1;
    
    void showPathSelection();
    void handleCombat();
    void handleShop();
    void handleEvent();
    void calculateAttackRounds();
    
public:
    void startGame(Difficulty diff);
    void mainLoop();
    Player* getPlayer();
    int getCurrentStage() const;
};
