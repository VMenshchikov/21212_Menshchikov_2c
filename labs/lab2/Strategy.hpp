#pragma once

#include <vector>

#include "PlayerHand.hpp"
#include "EnumAction.hpp"

class TStrategy {
  public:
    virtual EAction SelectAction(const THand& hand) = 0;
};