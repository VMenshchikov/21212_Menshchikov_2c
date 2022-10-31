#pragma once
#include "BlackJack.hpp"
#include "PlayerHand.hpp"

class TPlayer {
  public:
    bool ResultPart(THand &hand, int DilerScore);
    bool CheckStatus(THand &hand);

    // Take anouther card
    bool Hit(THand &hand, TBlackJack &Table);

    // Take no more cards
    bool Stand(THand &hand);

    // Increase the initial bet by 100% and take exactly one more card
    bool DoubleDown(THand &hand, TBlackJack &Table);

    // Create second hand from a starting hand
    // where both cards are the same value.
    bool Split(TBlackJack &Table);

    // Forfeit half the bet and end the hand immediately.
    bool Surrender(THand &hand);

    TPlayer(std::string StrategyName);

  private:
    TStrategy *Strategy;

    // before split DoubleDeck == true and create second hand
    bool DoubleDeck = false;

    // true - all card is visible
    // false - only first card
    bool Visible;

    THand FirstHand;
    THand SecondHand;

    int MyBank;

    bool Victory(THand &hand);
    bool Defeat(THand &hand);
};