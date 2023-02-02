#pragma once

#include "../../BlackJack/EnumAction.hpp"
#include "../../Factory/Factory.hpp"
#include "../Strategy.hpp"
#include <functional>
#include <iostream>

class TBlackJack;

class TDiler : public TStrategy {
  public:
    TDiler() = default;
    EAction SelectAction(const THand &hand, const TBlackJack &table);
};

namespace {
TStrategy *Create() { return new TDiler; }

const bool res = TFactory<std::string, TStrategy *,
                        std::function<TStrategy *()>>::GetInstance()
                   ->Register("Diler", Create);

bool Registration() {
    
    std::cout << "Diler is" << (res == true ? " " : " not ")
              << "registred in factory" << std::endl;
    return res;
}
const bool reg = Registration();
}