#include "Player.h"
#include <iostream>

Player::Player(Path path, Difficulty diff) 
    : chosenPath(path), gameDifficulty(diff) {}

int Player::getFinalHP() const {
    int total = baseHP + bonusHP;
    return (chosenPath == Path::ABUNDANCE) ? total * 1.5 : total;
}

// ...其他属性计算方法类似...

void Player::useResurrection() {
    if (hasResurrection) {
        baseHP = 100;
        bonusHP = 0;
        hasResurrection = false;
    }
}

void Player::printStatus() const {
    std::cout << "\n=== 玩家状态 ===\n"
              << "生命: " << getFinalHP() << "\n"
              << "攻击: " << getFinalATK() << "\n"
              << "速度: " << getFinalSPD() << "\n"
              << "金币: " << gold << "\n";
}
