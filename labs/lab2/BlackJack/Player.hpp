#pragma once
#include "BlackJack.hpp"
#include "PlayerHand.hpp"
#include <vector>

class TBlackJack;

class TPlayer {
  public:
    bool ResultPart(THand& hand, int DilerScore);
    const int GetSum(bool hand) const;
    const bool GetVisible() const;
    const std::vector<THand> GetHands() const;
    void MakeMove(TBlackJack &table);
    TPlayer(std::string StrategyName);

  private:
    TStrategy *Strategy;

    // before split DoubleDeck == true and create second hand
    // true - all card is visible
    // false - only first card
    bool Visible;

    std::vector<THand> Hands{THand()};

    int MyBank;

    bool Victory(THand &hand);
    bool Defeat(THand &hand);

    // false if score > 21
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

    void MoveHand(THand &hand, TBlackJack &table);
};