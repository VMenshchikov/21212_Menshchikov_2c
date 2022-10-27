#include "BlackJack.hpp"

THand::THand(){};

TStrategy::TStrategy(TBlackJack &table, int bet) : Table(table) {
    FirstHand.InGame = true;
    FirstHand.MyBet = bet;
    FirstHand.MyCards.push_back(table.TakeCard());
     

}

const int TStrategy::GetSum(THand &hand) const { return hand.MySum; }

void TStrategy::Victory(THand &hand) {
    MyBank += 2 * hand.MyBet;
    hand = THand();
}

void TStrategy::Defeat(THand &hand) { hand = THand(); }

void TStrategy::ResultPart(THand &hand, int DilerScore) {
    hand.MySum > DilerScore ? Victory(hand) : Defeat(hand);
}

bool TStrategy::CheckStatus(THand &hand) {
    if (hand.MySum > 21 && hand.CountA) {
        hand.MySum -= 10;
        hand.CountA--;
    }
    return hand.MySum > 21 ? hand.InGame = false : true;
}

bool TStrategy::Hit(THand &hand) {
    hand.MyCards.push_back(Table.TakeCard());
    hand.MySum += hand.MyCards.back();
    hand.NumStep++;
    return CheckStatus(hand);
}

bool TStrategy::Stand(THand &hand) { return false; }

bool TStrategy::DoubleDown(THand &hand) {
    hand.MyBet *= 2;
    return Hit(hand);
}

bool TStrategy::Split() {
    if (FirstHand.MyCards.size() > 2 ||
        FirstHand.MyCards.front() != FirstHand.MyCards.back() ||
        FirstHand.NumStep > 1) {
        std::cerr << "DoubleDeck failed";
        throw(1);
    }
    DoubleDeck = true;

    SecondHand.MyCards = {FirstHand.MyCards.back()};
    FirstHand.MySum -= FirstHand.MyCards.back();
    FirstHand.MyCards.pop_back();
    SecondHand.MySum = SecondHand.MyCards.front();

    SecondHand.MyBet = FirstHand.MyBet;
    SecondHand.InGame = true;

    Hit(FirstHand);
    FirstHand.NumStep--;
    Hit(SecondHand);
    SecondHand.NumStep--;
    return true;
}

bool TStrategy::Surrender(THand &hand) {
    if (hand.NumStep > 1) {
        std::cerr << "Surrender failed";
        throw(1);
    }
    MyBank += hand.MyBet / 2;
    hand.InGame = false;
}
