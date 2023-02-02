#pragma once

#include "../../BlackJack/EnumAction.hpp"
#include "../../Factory/Factory.hpp"
#include "../Strategy.hpp"
#include <functional>

class TBlackJack;

class TPlayerS : public TStrategy {
  public:
    TPlayerS() = default;
    EAction SelectAction(const THand &hand, const TBlackJack &table);
};

namespace {
TStrategy *Create() { return new TPlayerS; }

bool Print() {
    bool res = TFactory<std::string, TStrategy *,
                        std::function<TStrategy *()>>::GetInstance()
                   ->Register("Player", Create);
    std::cout << "Player is" << (res == true ? " " : " not ")
              << "registred in factory" << std::endl;
    return res;
}
const bool reg = Print();
} 
