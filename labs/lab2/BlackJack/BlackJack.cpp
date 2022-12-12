#include "BlackJack.hpp"
#include "../Factory/Factory.hpp"
#include "BlackJackSettings.hpp"
#include "Printer.hpp"

TBlackJack::TBlackJack(TConfig config) : Settings(TBlackJackSettings(config)) {
    CreateDeck();
    int countDiler = 0;
    for (auto i : Settings.PlayersStr) {
        if (i == "Diler") {
            countDiler++;
            if (countDiler > 1) {
                throw(std::invalid_argument("doubleDiller")); // popravit
            }
        }
        Players.push_back(
            TPlayer(i, (i == "Diler") ? SIZE_MAX : Settings.StartBank));
    };
}

void TBlackJack::CreateDeck() {
    if (Settings.ModeDeck) {
        for (int deck = 0; deck < Settings.ModeDeck; ++deck) {
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
        if (CurrentSizeDeck < 0.3 * Settings.ModeDeck * 52) {
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
    };
    return tmp;
}

void TBlackJack::StartGame() {
    if (Settings.ModeGame == "detailed") {
        Printer::PrintSeparation();
    };
    AllVisibleCards.clear();
    for (auto &i : Players) {
        auto &Hands = i.GetHands();
        Hands.clear();
        Hands.push_back(THand());
        if (i.GetBank() < Settings.Bet) {
            Hands[0].InGame = false;
            return;
        } else {
            if (&i != &(*Players.end()--)) {
                Hands[0].MyBet = Settings.Bet;
                i.GetBank() -= Settings.Bet;
            }
            Hands[0].InGame = true;
        }
        for (int j = 0; j < 2; ++j) {

            Hands[0].MyCards.push_back(GetCard(
                (!i.GetVisible() && Hands[0].MyCards.size() == 0) ? false
                                                                  : true));
            Hands[0].MySum += Hands[0].MyCards.back();
        }
    }
    DilerCard = Players.back().GetHands()[0].MyCards.back();
}

void TBlackJack::Play() {
    int countP = 0;
    for (auto &i : Players) {
        Printer::PrintPlayingPlayer(countP, Settings.PlayersStr);
        i.MakeMove(*this);
        countP++;
    };
}

void TBlackJack::Results() {
    int DilerScore = Players.back().GetSum(false);
    for (auto i = Players.begin(); i != Players.end()--; ++i) {
        for (auto &j : i->GetHands()) {
            i->ResultPart(j, DilerScore);
        }
    }
}

void TBlackJack::PrintResult() {
    std::vector<std::pair<int, int>> Winner = {{0, 0}}; // numPlayer, maxBank
    // size_t playersNum = 1;
    for (size_t playersNum = 0; playersNum < Players.size() - 1; ++playersNum) {
        std::cout << playersNum + 1
                  << ") Name: " << Settings.PlayersStr[playersNum]
                  << " | Bank: " << Players[playersNum].GetBank() << std::endl;
        if (Players[playersNum].GetBank() == Winner.begin()->second) {
            Winner.push_back({playersNum, Players[playersNum].GetBank()});

        } else {
            if (Players[playersNum].GetBank() > Winner.back().second) {
                Winner.clear();
                Winner.push_back({playersNum, Players[playersNum].GetBank()});
            }
        }
    }
    std::cout << std::endl << "Winner(s): ";
    for (int i = 0; i < Winner.size(); i++) {
        std::cout << Settings.PlayersStr[Winner[i].first] << " ";
    }
    std::cout << std::endl;
}
