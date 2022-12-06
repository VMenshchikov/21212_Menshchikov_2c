#include "Player.hpp"
#include "../Factory/Factory.hpp"
#include "Printer.hpp"
#include <functional>

TPlayer::TPlayer(std::string StrategyName, size_t bankSize) {
    Strategy = TFactory<std::string, TStrategy *,
                        std::function<TStrategy *()>>::GetInstance()
                   ->GetObject(StrategyName);
    Visible = StrategyName != "Diler";
    MyBank = bankSize;
    Hands.reserve(2);
}
size_t &TPlayer::GetBank() { return MyBank; };
const int TPlayer::GetSum(bool hand) const { return Hands[hand].MySum; }
const bool TPlayer::GetVisible() const { return Visible; }
std::vector<THand> &TPlayer::GetHands() { return Hands; }

void TPlayer::MoveHand(THand &hand, TBlackJack &table) {
    bool flag = true;
    bool detailed = table.GetModeGame() == "detailed" ? true : false;
    if (detailed) {
    }
    while (flag) {
        auto move = Strategy->SelectAction(hand, table);
        switch (move) {
        case (EAction::eHit):
            flag = Hit(hand, table);
            if (detailed) {
                Printer::PrintHit(hand, flag);
            }
            break;
        case (EAction::eStand):
            flag = Stand(hand);
            if (detailed) {
                Printer::PrintStand(hand);
            }

            break;
        case (EAction::eDoubleDoun):
            flag = DoubleDown(hand, table);
            if (detailed) {
                Printer::PrintDoubleDown(hand, flag);
            }

            break;
        case (EAction::eSplit): {
            flag = Split(table);
            if (detailed) {
                Printer::PrintSplit(Hands[0].MySum, Hands[1].MySum);
            }
            break;
        }
        case (EAction::eSurrender):
            flag = Surrender(hand);
            if (detailed) {
                Printer::PrintSurrender(MyBank);
            }
            break;
        default:
            std::cerr << "incorrenct action. Stand will bo executed.";
            flag = Stand(hand);
            Printer::PrintStand(hand);
            break;
        }
    };
}

void TPlayer::MakeMove(TBlackJack &table) {
    int countH = 1;
    for (auto i = Hands.begin(); i != Hands.end(); ++i, ++countH) {
        if (i->InGame) {
            if (table.GetModeGame() == "detailed") {
                Printer::PrintPlaingHand(countH);
            };
            MoveHand(*i, table);
        };
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
    hand.MyCards.push_back(Table.GetCard(true));
    hand.MySum += hand.MyCards.back();
    if (hand.MyCards.back() == 11) {
        hand.CountA++;
    }
    hand.NumStep++;
    return CheckStatus(hand);
}

bool TPlayer::Stand(THand &hand) { return false; }

bool TPlayer::DoubleDown(THand &hand, TBlackJack &Table) {
    if (MyBank < Table.GetBet() || hand.NumStep > 1) {
        std::cerr << "DoubleDown failed";
        return false;
    }
    MyBank -= hand.MyBet;
    hand.MyBet *= 2;
    return Hit(hand, Table);
}

bool TPlayer::Split(TBlackJack &Table) {
    if (Hands[0].MyCards.size() > 2 ||
        Hands[0].MyCards.front() != Hands[0].MyCards.back() ||
        Hands[0].NumStep > 1 || Hands.size() > 1 || MyBank < Table.GetBet()) {
        std::cerr << "Split failed";
        return false;
    }
    Hands.push_back(THand());

    Hands[1].MyCards.push_back(Hands[0].MyCards.back());

    Hands[0].MySum -= Hands[0].MyCards.back();
    Hands[0].MyCards.pop_back();
    Hands[1].MySum = Hands[1].MyCards.front();

    MyBank -= Table.GetBet();
    Hands[1].MyBet = Table.GetBet();
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
        return false;
    }
    MyBank += hand.MyBet / 2;
    hand.InGame = false;
    return false;
}
