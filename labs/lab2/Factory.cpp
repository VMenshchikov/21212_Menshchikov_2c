
#include "Factory.hpp"
#include "Strategy.hpp"

#include <map>
#include <string>

bool TStrategyFactory::RegisterStrategy(std::string NameStrategy,
                                        CreateStrategyCallBack Create) {
    GetInstance()->callbacks.insert({NameStrategy, Create});
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