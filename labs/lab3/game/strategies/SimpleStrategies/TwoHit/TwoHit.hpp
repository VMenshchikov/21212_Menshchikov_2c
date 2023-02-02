#pragma once

#include "../../../BlackJack/EnumAction.hpp"
#include "../../../Factory/Factory.hpp"
#include "../../Strategy.hpp"
#include <functional>
#include <iostream>

class TBlackJack;

class TTwoHit : public TStrategy {
  public:
    TTwoHit() = default;
    EAction SelectAction(const THand &hand, const TBlackJack &table);
};

namespace {
TStrategy *Create() { return new TTwoHit; }

const bool res = TFactory<std::string, TStrategy *,
                          std::function<TStrategy *()>>::GetInstance()
                     ->Register("TwoHit", Create);

bool Registration() {

    std::cout << "TwoHit is" << (res == true ? " " : " not ")
              << "registred in factory" << std::endl;
    return res;
}
const bool reg = Registration();
} // namespace