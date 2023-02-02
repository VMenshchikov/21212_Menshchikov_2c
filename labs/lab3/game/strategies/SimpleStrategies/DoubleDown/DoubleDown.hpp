#pragma once

#include "../../../Factory/Factory.hpp"
#include "../../Strategy.hpp"
#include <functional>
#include <iostream>

class TBlackJack;

class TDoubleDown : public TStrategy {
  public:
    TDoubleDown() = default;
    EAction SelectAction(const THand &hand, const TBlackJack &table);
};

namespace {
TStrategy *Create() { return new TDoubleDown; }

const bool res = TFactory<std::string, TStrategy *,
                          std::function<TStrategy *()>>::GetInstance()
                     ->Register("DoubleDown", Create);

bool Registration() {

    std::cout << "DoubleDown is" << (res == true ? " " : " not ")
              << "registred in factory" << std::endl;
    return res;
}
const bool reg = Registration();
} // namespace