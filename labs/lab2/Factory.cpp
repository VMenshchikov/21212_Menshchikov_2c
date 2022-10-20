
#include "Factory.hpp"
#include "Strategy.hpp"

#include <map>
#include <string>

bool TStrategyFactory::RegisterStrategy(std::string NameStrategy,
                                        CreateStrategyCallbeck Create) {
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

TStrategyFactory::TStrategyFactory(){};