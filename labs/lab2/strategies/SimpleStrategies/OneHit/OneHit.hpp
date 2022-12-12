#pragma once

#include "../../../Factory/Factory.hpp"
#include "../../Strategy.hpp"
#include <functional>
#include <iostream>

class TBlackJack;

class TOneHit : public TStrategy {
  public:
    TOneHit() = default;
    EAction SelectAction(const THand &hand, const TBlackJack &table);
};

namespace {
TStrategy *Create() { return new TOneHit; }

const bool res = TFactory<std::string, TStrategy *,
                          std::function<TStrategy *()>>::GetInstance()
                     ->Register("OneHit", Create);

bool Registration() {

    std::cout << "OneHit is" << (res == true ? " " : " not ")
              << "registred in factory" << std::endl;
    return res;
}
const bool reg = Registration();
} // namespace