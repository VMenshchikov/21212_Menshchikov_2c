#pragma once

#include <string>
#include <vector>

#include "BlackJack.hpp"

struct THand {
    THand();
    std::vector<int> MyCards = {};
    size_t CountA = 0; // TUZ
    size_t MySum = 0;
    size_t NumStep = 1;
    size_t MyBet = 0;
    bool InGame = false;
};

class TStrategy {
  public:
    TStrategy(TBlackJack &table, int bet);
    // return
    const int GetSum(THand& hand) const;
    void ResultPart(THand& hand, int DilerScore);

    // create object
    virtual TStrategy *Create() = 0;

    //
    virtual bool SelectAction() = 0;

  private:
    void Victory(THand &hand);
    void Defeat(THand &hand);

    bool CheckStatus(THand &hand);

    // Take anouther card
    bool Hit(THand& hand);

    // Take no more cards
    bool Stand(THand& hand);

    // Increase the initial bet by 100% and take exactly one more card
    bool DoubleDown(THand& hand);

    // Create second hand from a starting hand
    // where both cards are the same value.
    bool Split();

    // Forfeit half the bet and end the hand immediately.
    bool Surrender(THand& hand);

    // true - all card is visible
    // false - only first card
    bool Visible = true;

    // before split DoubleDeck == true and create second hand
    bool DoubleDeck = false;
    THand FirstHand;
    THand SecondHand;
    int MyBank;

    TBlackJack &Table;
};
