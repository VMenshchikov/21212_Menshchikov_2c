#pragma once

#include "Strategy.hpp"

#include <iostream>
#include <list>
#include <string>
#include <vector>



class TBlackJack {
  public:
    TBlackJack(int CountArg, char* args);
    void CreateDeck(int ModeDeck);
    int StartGame();

    const int TakeCard();
    const int GetSizeDeck() const;
    const std::list<int> TakeVisibleCards() const;

  private:
    std::vector<int> AllVisibleCards;
    int CurrentSizeDeck;
    std::list<int> CurrentDeck;

    TBlackJackSettings Settings;
};