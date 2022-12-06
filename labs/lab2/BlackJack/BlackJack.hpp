#pragma once

#include "BlackJackSettings.hpp"
#include "Player.hpp"

#include <iostream> //??
#include <list>
#include <string>
#include <vector>

class TPlayer;

class TBlackJack {
  public:
    TBlackJack(TConfig);

    int GetCard(bool visible);
    int GetDilerCard() const { return DilerCard; }
    int GetSizeDeck() const { return CurrentSizeDeck; }
    int GetBet() const { return Settings.Bet; }
    const std::string &GetModeGame() const { return Settings.ModeGame; }
    const std::vector<int> &GetVisibleCards() const { return AllVisibleCards; }
    int GetCountPart() { return Settings.CountPart; }

    void Game(size_t count) { // for tournament
        for (; count; --count) {
            StartGame();
            Play();
            Results();
        }
        PrintResult();
    }

  private:
    std::vector<int> AllVisibleCards = {};
    int CurrentSizeDeck;
    std::list<int> CurrentDeck;
    std::vector<TPlayer> Players;
    int DilerCard;
    const TBlackJackSettings Settings;

    void CreateDeck(int ModeDeck);

    void StartGame();
    void Play();
    void Results();
    void PrintResult();
};
