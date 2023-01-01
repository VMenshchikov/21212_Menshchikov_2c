#pragma once

#include <string>
#include <map>
#include <iostream>
#include <functional>

template <class KeyType, class ReturnType, class ReturnObjectCreator>
class TFactory {
  public:
    // Registering ObjCreator
    static bool Register(KeyType Key, ReturnObjectCreator Creator) {
        auto ret = GetInstance()->FMap.insert({Key, Creator});
        return ret.second;
    }

    // Removing ObjCreator from a factory
    bool Unregistred(KeyType Key) {
        return GetInstance()->FMap.erase(Key);
    }

    static TFactory<KeyType, ReturnType, ReturnObjectCreator> *GetInstance() {
        if (instance == nullptr) {
            instance = new TFactory<KeyType, ReturnType, ReturnObjectCreator>;
        }
        return instance;
    }

    ReturnType GetObject(KeyType Key) { return FMap[Key]; }

  private:
    typedef std::map<KeyType, ReturnObjectCreator> FactoryMap;
    FactoryMap FMap;

    static TFactory<KeyType, ReturnType, ReturnObjectCreator> *instance;

    TFactory<KeyType, ReturnType, ReturnObjectCreator>& operator=(TFactory &b) = delete;
    TFactory<KeyType, ReturnType, ReturnObjectCreator>(){};
    TFactory<KeyType, ReturnType, ReturnObjectCreator>(TFactory<KeyType, ReturnType, ReturnObjectCreator> &b) = delete;
};
// Init static value before using :
// Fucking shit ;}
//
template <class KeyType, class ReturnType, class ReturnObjectCreator>
TFactory<KeyType, ReturnType, ReturnObjectCreator>*
TFactory<KeyType, ReturnType, ReturnObjectCreator>::instance = nullptr;
