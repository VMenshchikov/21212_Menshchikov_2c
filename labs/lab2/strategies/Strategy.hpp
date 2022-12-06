#pragma once

#include <vector>
#include "../BlackJack/BlackJack.hpp"
#include "../BlackJack/PlayerHand.hpp"
#include "../BlackJack/EnumAction.hpp"

class TBlackJack;


class TStrategy {
  public:
    virtual EAction SelectAction(const THand& hand, const TBlackJack& table) = 0;
};