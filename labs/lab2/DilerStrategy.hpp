#pragma once

#include "EnumAction.hpp"
#include "Factory.hpp"
#include "Strategy.hpp"

class TDiler : public TStrategy {
  public:
    TDiler() = default;
    EAction SelectAction(const THand &hand);
};
