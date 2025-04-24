#pragma once
#include "Player.h"

class EventSystem {
public:
    enum EventType {
        NOTHING,        // 20%
        STAT_BOOST,     // 45%
        STAT_REDUCE,    // 20%
        ELITE_BATTLE,   // 10%
        RESURRECTION    // 5%
    };

    static void triggerRandomEvent(Player& player, int currentStage);
};
