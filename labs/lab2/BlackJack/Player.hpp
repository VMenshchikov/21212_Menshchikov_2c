#pragma once

#include "../strategies/Strategy.hpp"
#include "BlackJack.hpp"
#include "PlayerHand.hpp"
#include <vector>
#include <string>
#include <memory>
#include "../Factory/Factory.hpp"


class TBlackJack;
class TStrategy;

class TPlayer {
  public:
    bool ResultPart(THand& hand, int DilerScore);
    int GetSum(bool hand) const;
    size_t &GetBank();
    bool GetVisible() const;
    std::vector<THand>& GetHands();
    void MakeMove(TBlackJack &table);
    TPlayer(std::string StrategyName, size_t bankSize);

  private:
    std::unique_ptr<TStrategy> ptr;
    TStrategy *Strategy;

    // before split DoubleDeck == true and create second hand
    // true - all card is visible
    // false - only first card
    bool Visible;

    std::vector<THand> Hands;

    size_t MyBank;

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