#include "Player.h"
#include <iostream>

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

void Player::printStatus() const {
    std::cout << "\n=== 角色状态 ===\n"
              << "生命: " << getFinalHP() << " (+" << bonusHP << ")\n"
              << "攻击: " << getFinalATK() << " (+" << bonusATK << ")\n"
              << "速度: " << getFinalSPD() << " (+" << bonusSPD << ")\n"
              << "金币: " << gold << "\n";
}
