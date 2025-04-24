#pragma once
#include <string>
#include "Difficulty.h"

enum class Path { ABUNDANCE, DESTRUCTION, HUNT };

class Player {
public:
    Path chosenPath;
    Difficulty difficulty;
    
    // 基础属性
    int baseHP = 100;
    int baseATK = 100;
    int baseSPD = 100;
    
    // 祝福加成
    int bonusHP = 0;
    int bonusATK = 0;
    int bonusSPD = 0;
    
    int gold = 0;
    bool hasResurrection = false;
    int currentStage = 1;

    Player(Path path, Difficulty diff);
    
    // 属性计算
    int getFinalHP() const;
    int getFinalATK() const;
    int getFinalSPD() const;
    
    void applyBlessing(int hp, int atk, int spd);
    void useResurrection();
    void printStatus() const;
};
