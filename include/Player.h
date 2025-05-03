#pragma once
#include <string>

enum class Path { ABUNDANCE, DESTRUCTION, HUNT };
enum class Difficulty { EASY, NORMAL, HARD };

class Player {
public:
    Path chosenPath;
    Difficulty difficulty;
    int baseHP = 100;
    int baseATK = 30;
    int baseSPD = 50;
    int bonusHP = 0;
    int bonusATK = 0;
    int bonusSPD = 0;
    int gold = 0;
    bool hasResurrection = false;
    int currentStage = 1;  // 新增关卡进度字段

    Player(Path path, Difficulty diff);
    
    int getFinalHP() const;
    int getFinalATK() const;
    int getFinalSPD() const;
    
    void applyBlessing(int hp, int atk, int spd);
    void useResurrection();
    void printStatus() const;
};
