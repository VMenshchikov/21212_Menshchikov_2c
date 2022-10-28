#pragma once

#include "Strategy.hpp"
#include <string>
#include <vector>

class TBlackJackSettings {
  public:
    TBlackJackSettings(size_t bet, size_t countDeck, std::string modeGame,
                       std::vector<std::string> players);
    TBlackJackSettings(size_t bet, size_t countDeck,
                       std::vector<std::string> players);

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
    // the first is always the dealer
    std::vector<TStrategy *> Players;
    std::vector<std::string> PlayersStr;

    // 0 -- simple -- rand(10) + 1
    // 1 - 8 -- count of decks
    int ModeDeck = 0;
    int Bet;
};