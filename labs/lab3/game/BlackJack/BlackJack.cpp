#include "BlackJack.hpp"
#include "../Factory/Factory.hpp"
#include "BlackJackSettings.hpp"
#include "../../controller/controller.hpp"

#include <time.h>

TBlackJack::TBlackJack(TConfig config) : Settings(config), CurrentCountPart(config.countPart) {
    CreateDeck();
    int countDiler = 0;
    for (auto i : Settings.playersStr) {
        if (i == "Diler") {
            countDiler++;
            if (countDiler > 1) {
                throw(std::invalid_argument("doubleDiller"));
            }
        }
        Players.push_back(
            TPlayer(i, (i == "Diler") ? SIZE_MAX : Settings.startBank));
        if (i == "PlayerUI") {
            Settings.contr.connectUI(*(Players.back().getPlayer()));
        }
    };

}

void TBlackJack::CreateDeck() {
    if (Settings.countDeck) {
        for (size_t deck = 0; deck < Settings.countDeck; ++deck) {
            for (int j = 0; j < 4; j++) {
                CurrentDeck.insert(CurrentDeck.begin(), {2, 3, 4, 5, 6, 7, 8, 9,
                                                         10, 10, 10, 10, 11});
            }
        }
        CurrentSizeDeck = CurrentDeck.size();
        return;
    }
    CurrentSizeDeck = -1;
}

int TBlackJack::GetCard(bool visible, std::string name, bool pos, int count) {
    int tmp;
    if (CurrentSizeDeck == -1) {
        tmp = rand() % 10 + 2;
    } else {
        if (CurrentSizeDeck < 0.3 * Settings.countDeck * 52) {
            ReplenishmentDeck();
        }
        auto iter = CurrentDeck.begin();
        for (int i = 0; i < rand() % CurrentSizeDeck; ++i, ++iter)
            ;
        tmp = *iter;
        CurrentDeck.erase(iter);
        CurrentSizeDeck--;
    }
    if (visible) {
        AllVisibleCards.push_back(tmp);
    }
    emit newCard(tmp, name, visible, pos, count);
    return tmp;
}

void TBlackJack::newRevPause(int t) {
    revPause = t;
}


void TBlackJack::Game(size_t count, int aftherUI) {
    bool endFlag = false;
    for(;count && !endFlag;--count) {

        if (!aftherUI) { //afther ui slot call Game(*,1);
            StartGame();
            indLastP = 0;
        }

        if (Play()) { // ret 1 if UI (signal)
            CurrentCountPart = count;
            return;
        }
        Results();
        aftherUI = 0;
        emit dilerCard(GetDilerCard());
        if (Players.front().GetBank() < Settings.bet) {
            count = 1;
        }

        clock_t start = clock();
        while (clock() - start + revPause < 3000000){}


        if (count != 1){
            emit endPart();
        }

    }
    emit newBank(Players.front().GetBank(), Settings.bet);
    emit finalResult(Settings.startBank, Players.front().GetBank());
}

void TBlackJack::StartGame() {
    AllVisibleCards.clear();
    for (auto &i : Players) {
        auto &Hands = i.GetHands();
        Hands.clear();
        Hands.push_back(THand());
        if (i.GetBank() < Settings.bet) {
            Hands[0].InGame = false;
            return;
        } else {
            if (&i != &(*Players.end()--)) {
                Hands[0].MyBet = Settings.bet;
                i.GetBank() -= Settings.bet;
            }
            Hands[0].InGame = true;
        }
        for (int j = 0; j < 2; ++j) {
            Hands[0].MyCards.push_back(
                GetCard(i.GetVisible() || Hands[0].MyCards.size() != 0, i.getName(), false, j));
            Hands[0].MySum += Hands[0].MyCards.back();
        }
        if (i.getName() == "PlayerUI") {
            emit newBank(i.GetBank(), Settings.bet);

        }
    }
    DilerCard = Players.back().GetHands()[0].MyCards.front();
}

int TBlackJack::Play() {
    for (int i = indLastP; i < Players.capacity(); ++i) {
        auto &j = Players[i];
        if (j.MakeMove(*this)) { //player ui сама запросит карты
            return 1;            // если было запрошено действие
        }
        indLastP++;
    };
    return 0;
}

void TBlackJack::Results() {
    int DilerScore = Players.back().GetSum(false);
    for (auto i = Players.begin(); i != Players.end() - 1; ++i) {
        for (auto &j : i->GetHands()) {
            i->ResultPart(j, DilerScore);
        }
    }
}

void TBlackJack::setUIAct(std::string act) {
    EAction move;
    if (act == "H") {
        move = EAction::eHit;
    }
    if (act == "St") {
        move = EAction::eStand;
    }
    if (act == "DD") {
        move = EAction::eDoubleDoun;
    }
    if (act == "Sp") {
        move = EAction::eSplit;
    }
    if (act == "Su") {
        move = EAction::eSurrender;
    }

    Players.front().setUI(move);
    Game(CurrentCountPart, 1);
}
