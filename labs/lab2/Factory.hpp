#pragma once

#include "Strategy.hpp"
#include <map>
#include <string>

class TStrategyFactory {
  public:
    typedef TStrategy *(*CreateStrategyCallbeck)();

    // Registering a strategy
    static bool RegisterStrategy(std::string NameStrategy,
                                 CreateStrategyCallbeck Create);

    // Removing a strategy from a factory
    bool UnregistredStrategy(std::string NamStrategy);

    //TStrategy *CreateStrategy(std::string NameStrategy);

    static TStrategyFactory *GetInstance();

    TStrategy* GetObject(std::string objKey) {};

  private:
    typedef std::map<std::string, CreateStrategyCallbeck> CallbackMap;
    CallbackMap callbacks;

    static TStrategyFactory *instance;

    TStrategyFactory &operator=(TStrategyFactory &b) = delete;
    TStrategyFactory();
    TStrategyFactory(TStrategyFactory &b) = delete;
};
