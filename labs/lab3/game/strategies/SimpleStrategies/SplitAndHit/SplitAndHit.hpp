#pragma once

#include "../../../Factory/Factory.hpp"
#include "../../Strategy.hpp"
#include <functional>
#include <iostream>

class TBlackJack;

class TSplitAndHit : public TStrategy {
  public:
    TSplitAndHit() = default;
    EAction SelectAction(const THand &hand, const TBlackJack &table);
};

namespace {
TStrategy *Create() { return new TSplitAndHit; }

const bool res = TFactory<std::string, TStrategy *,
                          std::function<TStrategy *()>>::GetInstance()
                     ->Register("SplitAndHit", Create);

bool Registration() {

    std::cout << "SplitAndHit is" << (res == true ? " " : " not ")
              << "registred in factory" << std::endl;
    return res;
}
const bool reg = Registration();
} // namespace