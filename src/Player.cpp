#include "Player.h"
#include <iostream>

Player::Player(Path path, Difficulty diff) 
    : chosenPath(path), difficulty(diff) {}

int Player::getFinalHP() const {
    int total = baseHP + bonusHP;
    return (chosenPath == Path::ABUNDANCE) ? total * 1.5 : total;
}

int Player::getFinalATK() const {
    int total = baseATK + bonusATK;
    return (chosenPath == Path::DESTRUCTION) ? total * 1.5 : total;
}

int Player::getFinalSPD() const {
    int total = baseSPD + bonusSPD;
    return (chosenPath == Path::HUNT) ? total * 1.5 : total;
}

void Player::applyBlessing(int hp, int atk, int spd) {
    bonusHP += hp;
    bonusATK += atk;
    bonusSPD += spd;
}

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
