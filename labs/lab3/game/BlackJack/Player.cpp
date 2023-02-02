#include "Player.hpp"
#include "../Factory/Factory.hpp"
#include "../strategies/Strategy.hpp"
#include "../../controller/controller.hpp"
#include <functional>
#include <memory>

TPlayer::TPlayer(std::string StrategyName, size_t bankSize) :
        MyBank(bankSize), strategyName(StrategyName), Visible(StrategyName != "Diler") {
    ptr = std::unique_ptr<TStrategy>(
        TFactory<std::string, TStrategy *,
                 std::function<TStrategy *()>>::GetInstance()
            ->GetObject(StrategyName));
    Strategy = ptr.get();

    Visible = StrategyName != "Diler";
    Hands.reserve(2);
}
size_t &TPlayer::GetBank() { return MyBank; };
int TPlayer::GetSum(bool hand) const { return Hands[hand].MySum; }
bool TPlayer::GetVisible() const { return Visible; }
std::vector<THand> &TPlayer::GetHands() { return Hands; }
void TPlayer::setUI(EAction move) { ui = move; }

int TPlayer::MoveHand(THand &hand, TBlackJack &table) {
    bool flag = true;
    while (flag) {
        EAction move;
        if (ui == EAction::eNull) {
            move = Strategy->SelectAction(hand, table);
            if (this->getName() == "PlayerUI") {
                return 1;
            }
        } else {
            move = ui;
        }

        switch (move) {
        case (EAction::eHit):
            flag = Hit(hand, table);
            break;
        case (EAction::eStand):
            flag = Stand(hand);
            break;
        case (EAction::eDoubleDoun):
            flag = DoubleDown(hand, table);

            break;
        case (EAction::eSplit): {
            flag = Split(table);
            break;
        }
        case (EAction::eSurrender):
            flag = Surrender(hand);
            break;
        default:
            std::cerr << "incorrenct action. Stand will bo executed.";
            flag = Stand(hand);
            break;
        }
        ui = EAction::eNull;
    }
    return 0;
}

int TPlayer::MakeMove(TBlackJack &table) {
    for (auto i = Hands.begin(); i != Hands.end(); ++i) {
        if (i->InGame) {
            if (MoveHand(*i, table)) return 1;
        }
    }
    return 0;
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
    if (!hand.InGame) return Defeat(hand);
    if (DilerScore > 21) return Victory(hand);
    return (hand.MySum > DilerScore) ? Victory(hand) : Defeat(hand);
}

bool TPlayer::CheckStatus(THand &hand) {
    if (hand.MySum > 21 && hand.CountA) {
        hand.MySum -= 10;
        hand.CountA--;
    }
    return hand.MySum > 21 ? hand.InGame = false : true;
}

bool TPlayer::Hit(THand &hand, TBlackJack &Table) {
    hand.MyCards.push_back(Table.GetCard(true, this->getName(), &(this->GetHands()[1]) == &hand, hand.MyCards.size()));
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
    if (Hands[0].MyCards.capacity() > 2 ||
        Hands[0].MyCards.front() != Hands[0].MyCards.back() ||
        Hands[0].NumStep > 1 || MyBank < Table.GetBet()) {
        std::cerr << "Split failed " << (Hands[0].MyCards.capacity() > 2) << " " <<
                    (Hands[0].MyCards[0] != Hands[0].MyCards[1]) << " " <<
                     (Hands[0].NumStep > 1) << " " << (MyBank < Table.GetBet());
        std::cerr << Hands[0].MyCards[0] << " " << Hands[0].MyCards[1];
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
