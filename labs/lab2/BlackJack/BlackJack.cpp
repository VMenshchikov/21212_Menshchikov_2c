#include "BlackJack.hpp"
#include "../Factory/Factory.hpp"
#include "BlackJackSettings.hpp"
#include "Printer.hpp"

TBlackJack::TBlackJack(TConfig config) : Settings(config) {
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
    };
}


void TBlackJack::CreateDeck() {
    if (Settings.countDeck) {
        for (int deck = 0; deck < Settings.countDeck; ++deck) {
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

int TBlackJack::GetCard(bool visible) {
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
    return tmp;
}

void TBlackJack::StartGame() {
    if (Settings.modeGame == "detailed") {
        Printer::PrintSeparation();
    };
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
                GetCard(i.GetVisible() || Hands[0].MyCards.size() != 0));
            Hands[0].MySum += Hands[0].MyCards.back();
        }
    }
    DilerCard = Players.back().GetHands()[0].MyCards.back();
}

void TBlackJack::Play() {
    int countP = 0;
    for (auto &i : Players) {
        Printer::PrintPlayingPlayer(countP, Settings.playersStr);
        i.MakeMove(*this);
        countP++;
    };
    if (Settings.modeGame == "detailed") {
        Printer::PrintSeparationPlayers();
        Printer::PrintDillerCards(Players.back().GetHands()[0].MyCards);
    }
    Printer::PrintNN();
}

void TBlackJack::Results() {

    int DilerScore = Players.back().GetSum(false);
    for (auto i = Players.begin(); i != Players.end() - 1; ++i) {
        for (auto &j : i->GetHands()) {
            i->ResultPart(j, DilerScore);
        }
    }
}

void TBlackJack::PrintResult() {
    std::vector<std::pair<int, int>> Winner = {{0, 0}}; // numPlayer, maxBank
    for (size_t playersNum = 0; playersNum < Players.size()-1; ++playersNum) {
        Printer::PrintPlayerResult(Settings.playersStr[playersNum],
                                   Players[playersNum].GetBank(),
                                   playersNum + 1);
        if (Players[playersNum].GetBank() == Winner.begin()->second) {
            Winner.push_back({playersNum, Players[playersNum].GetBank()});

        } else {
            if (Players[playersNum].GetBank() > Winner.back().second) {
                Winner.clear();
                Winner.push_back({playersNum, Players[playersNum].GetBank()});
            }
        }
    }

    std::vector<std::string> winnersStr;
    for (auto i : Winner) {
        winnersStr.push_back(Settings.playersStr[i.first]);
    }
    Printer::PrintWinner(winnersStr);
}
