#pragma once
#include <string>

class Enemy {
public:
    std::string name;
    int hp, atk, spd;
    int stageLevel;
    
    Enemy(int stage, Difficulty diff);
    void printStats() const;

private:
    void generateName(int stage);
    void scaleStats(int stage, Difficulty diff);
};
