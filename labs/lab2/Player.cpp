#include "Player.hpp"

// const int TPlayer::GetSum(THand &hand) const { return hand.MySum; }

bool TPlayer::Victory(THand &hand) {
    MyBank += hand.MyBet * 2;
    hand = THand();
    return true;
}

bool TPlayer::Defeat(THand &hand) {
    hand = THand();
    return false;
}

bool TPlayer::ResultPart(THand &hand, int DilerScore) {
    return hand.MySum > DilerScore ? Victory(hand) : Defeat(hand);
}

bool TPlayer::CheckStatus(THand &hand) {
    if (hand.MySum > 21 && hand.CountA) {
        hand.MySum -= 10;
        hand.CountA--;
    }
    return hand.MySum > 21 ? hand.InGame = false : true;
}

bool TPlayer::Hit(THand &hand, TBlackJack &Table) {
    hand.MyCards.push_back(Table.GetCard(Visible));
    hand.MySum += hand.MyCards.back();
    hand.NumStep++;
    return CheckStatus(hand);
}

bool TPlayer::Stand(THand &hand) { return false; }

bool TPlayer::DoubleDown(THand &hand, TBlackJack &Table) {
    hand.MyBet *= 2;
    return Hit(hand, Table);
}

bool TPlayer::Split(TBlackJack& Table) {
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

    Hit(FirstHand, Table);
    FirstHand.NumStep--;
    Hit(SecondHand, Table);
    SecondHand.NumStep--;
    return true;
}

bool TPlayer::Surrender(THand &hand) {
    if (hand.NumStep > 1) {
        std::cerr << "Surrender failed";
        throw(1);
    }
    MyBank += hand.MyBet / 2;
    hand.InGame = false;
}
