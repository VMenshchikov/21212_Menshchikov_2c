#pragma once

#include "../game/BlackJack/EnumAction.hpp"
//#include "../interface/BlackJack/Factory/Factory.hpp"
#include "../game/strategies/Strategy.hpp"
#include <functional>

class TBlackJack;

class TPlayerUI : public TStrategy {
    Q_OBJECT
  public:
    TPlayerUI() = default;
    EAction SelectAction(const THand &hand, const TBlackJack &table);

  signals:
    void needMove(THand, const TBlackJack*);
  private:
    std::string act;
};

//registred
namespace {
TStrategy *Create() { return new TPlayerUI; }

bool Print() {
    bool res = TFactory<std::string, TStrategy *,
                        std::function<TStrategy *()>>::GetInstance()
                   ->Register("PlayerUI", Create);
    std::cout << "PlayerUI is" << (res == true ? " " : " not ")
              << "registred in factory" << std::endl;
    return res;
    }
const bool reg = Print();
}

