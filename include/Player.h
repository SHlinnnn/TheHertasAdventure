#pragma once
#include <string>

enum class Path { ABUNDANCE, DESTRUCTION, HUNT };

class Player {
public:
    // 命途加成
    Path chosenPath;
    
    // 基础属性
    int baseHP = 100;
    int baseATK = 100;
    int baseSPD = 100;
    
    // 祝福加成
    int bonusHP = 0;
    int bonusATK = 0;
    int bonusSPD = 0;
    
    // 游戏进度
    int gold = 0;
    bool hasResurrection = false;

    // 系统方法
    int getFinalHP() const;
    int getFinalATK() const;
    int getFinalSPD() const;
    void applyBlessing(int hp, int atk, int spd);
    void printStatus() const;
};
