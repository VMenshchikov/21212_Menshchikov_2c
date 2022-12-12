#pragma once

#include "../../BlackJack/EnumAction.hpp"
#include "../../Factory/Factory.hpp"
#include "../Strategy.hpp"
#include <functional>
#include <iostream>

class TBlackJack;

class TCopyDiler : public TStrategy {
  public:
    TCopyDiler() = default;
    EAction SelectAction(const THand &hand, const TBlackJack &table);
};

namespace {
TStrategy *Create() { return new TCopyDiler; }

const bool res = TFactory<std::string, TStrategy *,
                        std::function<TStrategy *()>>::GetInstance()
                   ->Register("CopyDiler", Create);

bool Registration() {
    
    std::cout << "CopyDiler is" << (res == true ? " " : " not ")
              << "registred in factory" << std::endl;
    return res;
}
const bool reg = Registration();
}