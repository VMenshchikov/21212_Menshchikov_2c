#pragma once

#include "Strategy.hpp"

#include <iostream>
#include <list>
#include <string>
#include <vector>

class TBlackJackSettings {
  public:
    TBlackJackSettings(std::string AllArgs);

    const std::string GetModeGame() const;
    const std::string GetPlayers() const;
    const int GetDeckMode() const;

  private:
    // detailed/fast/tournament
    // detailed - full game detail
    // fast - only result
    // tournament - ranked list with win percentage
    std::string ModeGame;

    // all participating strategies
    // the first is always the dealer
    std::vector<TStrategy> Players;

    // 0 -- simple -- rand(10) + 1
    // 1 - 8 -- count of decks
    int ModeDeck = 0;
    int Bet;
};

class TBlackJack {
  public:
    TBlackJack(std::string AllArgs);
    void CreateDeck(int ModeDeck);
    int StartGame();

    friend const int TakeCard(TBlackJack &table);
    friend const int GetSizeDeck(const TBlackJack &table);
    friend const std::list<int> TakeVisibleCards(const TBlackJack &table);

  private:
    std::vector<int> AllVisibleCards;
    int CurrentSizeDeck;
    std::list<int> CurrentDeck;

    TBlackJackSettings Settings;
};