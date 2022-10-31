#pragma once

#include "Strategy.hpp"
#include <map>
#include <string>

class TStrategyFactory {
  public:
    typedef TStrategy *(*CreateStrategyCallBack)();

    // Registering a strategy
    static bool RegisterStrategy(std::string NameStrategy,
                                 CreateStrategyCallBack Create);

    // Removing a strategy from a factory
    bool UnregistredStrategy(std::string NamStrategy);

    static TStrategyFactory *GetInstance();

    TStrategy* GetObject(std::string objKey) {};

  private:
    typedef std::map<std::string, CreateStrategyCallBack> CallbackMap;
    CallbackMap callbacks;

    static TStrategyFactory *instance;

    TStrategyFactory &operator=(TStrategyFactory &b) = delete;
    TStrategyFactory();
    TStrategyFactory(TStrategyFactory &b) = delete;
};
