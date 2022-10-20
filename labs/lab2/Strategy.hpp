#pragma once

#include <string>
#include <vector>

#include "BlackJack.hpp"

struct THand {
    THand(std::vector<int> cards, int bet);
    THand();
    std::vector<int> MyCards;
    int MySum;
    int NumStep = 1;
    int MyBet;
};

class TStrategy{
  public:
    // return
    const int GetSum(int NumHand) const;
    void Victory(int NumHand);
    void Defeat(int NumHand);

    // create object
    virtual TStrategy *Create();

    virtual bool SelectAction();

  private:
    // Take anouther card
    void Hit(int NumHand);

    // Take no more cards
    void Stand(int NumHand);

    // Increase the initial bet by 100% and take exactly one more card
    void DoubleDown(int NumHand);

    // Create second hand from a starting hand
    // where both cards are the same value.
    void Split();

    // Forfeit half the bet and end the hand immediately.
    void Surrender(int NumHand);


    // true - all card is visible
    // false - only first card
    bool Visible = true;

    // before split DoubleDeck == true and create second hand
    bool DoubleDeck = false;
    THand FirstHand;
    THand SecondHand;
    int MyBank;
};