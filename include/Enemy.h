#pragma once
#include <string>

enum Difficulty { EASY, MEDIUM, HARD };

class Enemy {
public:
    std::string name;
    int hp, atk, spd;
    
    Enemy(int stageLevel, Difficulty diff);
    void printStats() const;
    
private:
    void generateName(int stage);
    void scaleStats(int stage, Difficulty diff);
};
