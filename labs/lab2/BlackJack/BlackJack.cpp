#include "BlackJack.hpp"
#include "../Factory/Factory.hpp"
#include "BlackJackSettings.hpp"
#include "Printer.hpp"


TBlackJack::TBlackJack(TConfig config) : Settings(TBlackJackSettings(config)) {
    CurrentSizeDeck = Settings.ModeDeck == 0 ? -1 : Settings.ModeDeck * 52;

    CreateDeck(Settings.ModeDeck);
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

void TBlackJack::CreateDeck(int ModeDeck) {
    if (ModeDeck) {
        for (int deck = 0; deck < ModeDeck; ++deck) {
            for (int j = 0; j < 4; j++) {
                CurrentDeck.insert(CurrentDeck.begin(), {2, 3, 4, 5, 6, 7, 8, 9,
                                                         10, 10, 10, 10, 11});
            }
        }
    }
}

int TBlackJack::GetCard(bool visible) {
    int tmp;
    if (CurrentSizeDeck == -1) {
        tmp = rand() % 10 + 2;
    } else {
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
    std::vector<std::pair<int, int>> Winner = {
        {1, Players.begin()->GetBank()}}; // numPlayer, maxBank
    size_t playersNum = 1;
    for (auto i = Players.begin(); i != Players.end() - 1; ++i) {
        std::cout << playersNum
                  << ") Name: " << Settings.PlayersStr[playersNum - 1]
                  << " | Bank: " << i->GetBank() << std::endl;
        if (i->GetBank() == Winner.begin()->second && playersNum > 1) {
            Winner.push_back({playersNum, i->GetBank()});

        } else {
            if (i->GetBank() < Winner.begin()->second) {
                Winner.clear();
                Winner.push_back({playersNum, i->GetBank()});
            }
        }
        playersNum++;
    }
    std::cout << std::endl << "Winner(s): ";
    for (auto i : Winner) {
        std::cout << Settings.PlayersStr[i.first];
    }
}
