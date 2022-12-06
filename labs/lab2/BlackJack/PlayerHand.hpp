#pragma once

#include <vector>

struct THand {
    std::vector<int> MyCards = {};
    size_t CountA = 0; // TUZ
    size_t MySum = 0;
    size_t NumStep = 1;
    size_t MyBet = 0;
    bool InGame = false;
};