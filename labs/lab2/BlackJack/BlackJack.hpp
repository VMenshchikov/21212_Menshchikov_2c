#pragma once

#include "BlackJackSettings.hpp"
#include "Player.hpp"
#include "Printer.hpp"

#include <list>
#include <string>
#include <vector>

class TPlayer;

class TBlackJack {
  public:
    TBlackJack(TConfig config);

    int GetCard(bool visible);
    int GetDilerCard() const { return DilerCard; }
    int GetSizeDeck() const { return CurrentSizeDeck; }
    int GetBet() const { return Settings.bet; }
    const std::string &GetModeGame() const { return Settings.modeGame; }
    const std::vector<int> &GetVisibleCards() const { return AllVisibleCards; }
    int GetCountPart() { return Settings.countPart; }

    void Game(size_t count) { // for tournament
        Printer::PrintSeparationPlayers();

        for (; count; --count) {
            StartGame();
            Printer::PrintSeparationPlayers();

            Play();
            Printer::PrintSeparationPlayers();

            Results();
        }
        Printer::PrintSeparationPlayers();

        PrintResult();
    }

  private:
    std::vector<int> AllVisibleCards = {};
    int CurrentSizeDeck;
    std::list<int> CurrentDeck;
    std::vector<TPlayer> Players;
    int DilerCard;
    const TConfig Settings;

    void CreateDeck();
    void ReplenishmentDeck() { CreateDeck(); };

    void StartGame();
    void Play();
    void Results();
    void PrintResult();
};
