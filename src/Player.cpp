#pragma once
#include <string>
#include <vector>

enum class Path { ABUNDANCE, DESTRUCTION, HUNT };
enum Difficulty { EASY, MEDIUM, HARD };

class Player {
public:
    // 命途系统
    Path chosenPath;
    Difficulty gameDifficulty;
    
    // 基础属性
    int baseHP = 100;
    int baseATK = 100;
    int baseSPD = 100;
    
    // 祝福加成
    int bonusHP = 0;
    int bonusATK = 0;
    int bonusSPD = 0;
    
    // 游戏状态
    int gold = 0;
    bool hasResurrection = false;
    int currentStage = 1;

    // 系统方法
    Player(Path path, Difficulty diff);
    
    int getFinalHP() const;
    int getFinalATK() const;
    int getFinalSPD() const;
    
    void applyBlessing(int hp, int atk, int spd);
    void useResurrection();
    void printStatus() const;
};
