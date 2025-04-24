#pragma once
#include <string>
#include "Difficulty.h"

class Enemy {
public:
    std::string name;
    int hp;
    int atk;
    int spd;

    Enemy(int stage, Difficulty diff);
    void printStats() const;

private:
    void generateName(int stage);
    void scaleStats(int stage, Difficulty diff);
};
