#include "Player.hpp"

const int TPlayer::GetSum(bool hand) const { return Hands[hand].MySum; }
const bool TPlayer::GetVisible() const { return Visible; }
const std::vector<THand> TPlayer::GetHands() const { return Hands; }

void TPlayer::MoveHand(THand &hand, TBlackJack &table) {
    bool flag = true;
    while (flag) {
        auto move = Strategy->SelectAction(hand);
        switch (move) {
        case (eHit):
            flag = Hit(hand, table);
            break;
        case (eStand):
            flag = Stand(hand);
            break;
        case (eDoubleDoun):
            flag = DoubleDown(hand, table);
            break;
        case (eSplit):
            flag = Split(table);
            break;
        case (eSurrender):
            flag = Surrender(hand);
            break;
        default:
            flag = false;
            break;
        }
    };
}

void TPlayer::MakeMove(TBlackJack &table) {
    for (auto i : Hands) {
        MoveHand(i, table);
    }
}

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
    if (!hand.MyCards.size()) {
        return false;
    }
    return ((hand.MySum > DilerScore) && hand.InGame) ? Victory(hand)
                                                      : Defeat(hand);
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

bool TPlayer::Split(TBlackJack &Table) {
    if (Hands[0].MyCards.size() > 2 ||
        Hands[0].MyCards.front() != Hands[0].MyCards.back() ||
        Hands[0].NumStep > 1 || Hands.size() > 2) {
        std::cerr << "DoubleDeck failed";
        throw(1);
    }
    Hands.push_back(THand());

    Hands[1].MyCards = {Hands[0].MyCards.back()};
    Hands[0].MySum -= Hands[0].MyCards.back();
    Hands[0].MyCards.pop_back();
    Hands[1].MySum = Hands[1].MyCards.front();

    Hands[1].MyBet = Hands[0].MyBet;
    Hands[1].InGame = true;

    Hit(Hands[0], Table);
    Hands[0].NumStep--;
    Hit(Hands[1], Table);
    Hands[1].NumStep--;
    return true;
}

bool TPlayer::Surrender(THand &hand) {
    if (hand.NumStep > 1) {
        std::cerr << "Surrender failed";
        throw(1);
    }
    MyBank += hand.MyBet / 2;
    hand.InGame = false;
    return false;
}
