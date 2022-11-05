#pragma once

#include "../../BlackJack/EnumAction.hpp"
#include "../../Factory/Factory.hpp"
#include "../Strategy.hpp"

class TDiler : public TStrategy {
  public:
    TDiler() = default;
    EAction SelectAction(const THand &hand);
};
