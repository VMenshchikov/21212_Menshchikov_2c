#include "BlackJack.hpp"
#include "BlackJackSettings.hpp"
#include "../Factory/Factory.hpp"
//{ TabWidth: 4, IndentWidth: 4, ColumnLimit: 80 }

TPlayer::TPlayer(std::string StrategyName) {
    Strategy = (TStrategyFactory::GetInstance()->GetObject(StrategyName));
    Visible = StrategyName != "Diler";
}

TBlackJack::TBlackJack(TConfig config) : Settings(TBlackJackSettings(config)) {
    CurrentSizeDeck =
        Settings.GetModeDeck() == 0 ? -1 : Settings.GetModeDeck() * 52;

    CreateDeck(Settings.GetModeDeck());

    for (auto i : Settings.GetPlayers()) {
        Players.push_back(TPlayer(i));
    }
};

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

const int TBlackJack::GetCard(bool visible) {
    int tmp;
    if (!CurrentSizeDeck) {
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
    }
    return tmp;
}

const int TBlackJack::GetSizeDeck() const { return CurrentSizeDeck; }

const std::vector<int> TBlackJack::GetVisibleCards() const {
    return AllVisibleCards;
}

void TBlackJack::StartGame() {
    for (auto i : Players) {
        auto Hands = i.GetHands();
        for (int j = 0; j < 2; ++j) {
            Hands[0].MyCards.push_back(GetCard(i.GetVisible()));
            Hands[0].MySum += Hands[0].MyCards.back();
        }
    }
}

void TBlackJack::Play() {
    for (auto i : Players) {
        i.MakeMove(*this);
    };
}

void TBlackJack::Results() {
    int DilerScore = Players.end()->GetSum(0);
    for (auto i = Players.begin(); i != Players.end()--; ++i) {
        auto Hands = i->GetHands();
        i->ResultPart(Hands[0], DilerScore);
        i->ResultPart(Hands[1], DilerScore);
    }
}
