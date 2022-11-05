#pragma once

#include "../strategies/Strategy.hpp"
#include <string>
#include <vector>

struct TConfig {
    //--bank={bank_size, bet_size}                  //always
    size_t bet;
    size_t bank;
    //--players={name1, name2, name3} (min1)        //always
    std::vector<std::string> players;
    //--deck=*deck_size* (0-8)                      //default = 0
    size_t countDeck = 0;
    //--mode=[detailed|fast|tournament]             //optional
    std::string modeGame;

    TConfig(size_t bet, size_t bank, std::vector<std::string> players,
            std::string modeGame, size_t countDeck = 0);
    TConfig(size_t bet, size_t bank, std::vector<std::string> players,
            size_t countDeck = 0);
    TConfig(int argc, char **argv);
};

class TBlackJackSettings {
  public:
    TBlackJackSettings(TConfig config);

    const std::string GetModeGame() const;
    const std::vector<std::string> GetPlayers() const;
    const int GetModeDeck() const;

  private:
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
    int Bet;
    int StartBank;
};