#pragma once

#include <string>
#include <vector>
#include "../Factory/Factory.hpp"

class TController;

struct TConfig {
    //--bank={bank_size, bet_size}                  //always
    size_t bet;
    size_t startBank;
    size_t countPart;

    //--players={name1, name2, name3} (min1)        //always
    // all participating strategies
    // diler always last "Player"
    std::vector<std::string> playersStr;

    //--deck=*deck_size* (0-8)                      //default = 0
    // 0 -- simple -- rand()
    // 1 - 8 -- count of decks
    size_t countDeck = 0;

    // detailed/tournament
    // detailed - full game detail
    // tournament - all results and winner
    std::string modeGame;

    TController &contr;

    TConfig(TController &contr, size_t srandPar, size_t bet, size_t bank,
            std::vector<std::string>&& players, std::string modeGame,
            size_t countDeck = 0, size_t countPart = 1);
};
