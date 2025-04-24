#pragma once
#include <string>

enum class Path { ABUNDANCE, DESTRUCTION, HUNT };
enum Difficulty { EASY, MEDIUM, HARD };

class Player {
public:
    // 游戏状态
    Path chosenPath;
    Difficulty gameDifficulty;
    int currentStage = 1;
    
    // 基础属性
    int baseHP = 100;
    int baseATK = 100;
    int baseSPD = 100;
    
    // 祝福加成
    int bonusHP = 0;
    int bonusATK = 0;
    int bonusSPD = 0;
    
    // 经济系统
    int gold = 0;
    bool hasResurrection = false;

    Player(Path path, Difficulty diff);
    
    // 属性计算
    int getFinalHP() const;
    int getFinalATK() const;
    int getFinalSPD() const;
    
    // 系统方法
    void applyBlessing(int hp, int atk, int spd);
    void useResurrection();
    void printStatus() const;
};
