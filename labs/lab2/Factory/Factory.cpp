
#include "Factory.hpp"
#include "../strategies/Strategy.hpp"

#include <map>
#include <string>

bool TStrategyFactory::RegisterStrategy(std::string NameStrategy,
                                        CreateStrategyCallBack Create) {
    auto ret = GetInstance()->callbacks.insert({NameStrategy, Create});
    return ret.second;
}

bool TStrategyFactory::UnregistredStrategy(std::string NameStrategy) {
    return GetInstance()->callbacks.erase(NameStrategy);
}

TStrategyFactory *TStrategyFactory::instance = nullptr;

TStrategyFactory *TStrategyFactory::GetInstance() {
    if (instance == nullptr) {
        instance = new TStrategyFactory;
    }
    return instance;
}

TStrategy* TStrategyFactory::GetObject(std::string objKey) {
      return callbacks[objKey]();
    }

TStrategyFactory::TStrategyFactory(){};