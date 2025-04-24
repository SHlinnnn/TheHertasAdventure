#pragma once
#include "Player.h"

class EventSystem {
public:
    enum Result {
        NOTHING,
        STAT_UP,
        STAT_DOWN,
        HARD_BATTLE,
        RESURRECTION
    };

    static Result trigger(Player& player, int stage);
};
