#pragma once

// #include "../strategies/Strategy.hpp"
#include <string>
#include <vector>

struct TConfig {
    //--bank={bank_size, bet_size}                  //always
    size_t bet;
    size_t bank;
    size_t countPart;
    //--players={name1, name2, name3} (min1)        //always
    std::vector<std::string> players;
    //--deck=*deck_size* (0-8)                      //default = 0
    size_t countDeck = 0;
    //--mode=[detailed|fast|tournament.countPart?]  //optional
    std::string modeGame;
    

    TConfig(size_t srandPar, size_t bet, size_t bank,
            std::vector<std::string>&& players, std::string modeGame,
            size_t countDeck = 0, size_t countPart = 1);
    TConfig(int argc, char **argv);
};

struct TBlackJackSettings {
  public:
    TBlackJackSettings(TConfig config);

    // detailed/fast/tournament
    // detailed - full game detail
    // fast - only result
    // tournament - ranked list with win percentage
    std::string ModeGame;

    // all participating strategies
    // diler always last "Player"
    std::vector<std::string> PlayersStr;

    // 0 -- simple -- rand(10) + 1
    // 1 - 8 -- count of decks
    int ModeDeck = 0;
    size_t CountPart;
    int Bet;
    size_t StartBank;
};