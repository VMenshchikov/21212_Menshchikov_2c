#include "BlackJack.hpp"
#include "BlackJackSettings.hpp"
#include "Factory.hpp"
//{ TabWidth: 4, IndentWidth: 4, ColumnLimit: 80 }

TPlayer::TPlayer(std::string StrategyName) {
    Strategy = (TStrategyFactory::GetInstance()->GetObject(StrategyName));
    Visible = StrategyName == "Diler" ? false : true;
}

TBlackJack::TBlackJack(TConfig config) : Settings(TBlackJackSettings(config)) {
    CurrentSizeDeck =
        Settings.GetModeDeck() == 0 ? -1 : Settings.GetModeDeck() * 52;

    CreateDeck(Settings.GetModeDeck());

    Players.push_back(TPlayer("Diler"));
    for (auto i : Settings.GetPlayers()) {
        Players.push_back(TPlayer(i));
    }
};

void TBlackJack::CreateDeck(int ModeDeck) {
    if (ModeDeck) {
        for (int deck = 0; deck < ModeDeck; ++deck) {
            for (int i = 2; i <= 11; ++i) {
                for (int j = 0; j < 4; j++) {
                    CurrentDeck.push_back(i);
                }
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