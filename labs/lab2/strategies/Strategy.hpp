#pragma once

#include <vector>

#include "../BlackJack/PlayerHand.hpp"
#include "../BlackJack/EnumAction.hpp"

class TStrategy {
  public:
    virtual EAction SelectAction(const THand& hand) = 0;
};